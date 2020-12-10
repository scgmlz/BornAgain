"""
Process gitlog and create a file with number of lines of code.
"""
from datetime import datetime
from .file_types import FileTypes, filetype
import re
from email.utils import parsedate
import subprocess


def gitlog():
    """
    Execute gitlog command and make generator over lines in the log
    """
    p = subprocess.Popen(['git', 'log', 'develop', '--reverse', '-p'], stdout=subprocess.PIPE)
    for line in iter(p.stdout.readline, b''):
        decoded = line.decode('latin1')
        if decoded and len(decoded):
            yield decoded.strip()


class Commit:
    """
    Contains commit info and accumulated number of lines of code (file type dependent).
    """
    def __init__(self):
        self.date = datetime.today()
        self.added_lines = 0
        self.removed_lines = 0
        self.loc_for_type = FileTypes.loc_for_type()
        self.hsh = None
        self.who = None
        self.cmt = None

    def increment_loc(self, file_type):
        self.loc_for_type[file_type] += 1
        self.added_lines += 1

    def decrement_loc(self, file_type):
        self.loc_for_type[file_type] -= 1
        self.removed_lines += 1


class DayHistory:
    """
    Number of lines added or deleted for given day.
    """
    def __init__(self, date, locs):
        self.date = date
        self.loc_for_type = locs


class HistoryCollector:
    def __init__(self):
        self.last_commit = Commit()
        self.data = []
        self.locs = 0
        self.fc = 0
        self.file_type_ppp = FileTypes.UNDEF
        self.file_type_mmm = FileTypes.UNDEF
        self.start_date = datetime(2012, 4, 1)
        self.days_history = {}  # DayHistory vs. number of days since beginning of coding

    def pop(self):
        if not self.last_commit.added_lines:
            return
        pstr="%s %8u %5s %5s %7s %s"%(self.last_commit.date, self.locs, '+' + str(self.last_commit.added_lines), '-' + str(self.last_commit.removed_lines), self.last_commit.hsh, self.last_commit.who)
        print(pstr)
        delta = (self.last_commit.date - self.start_date).days
        self.days_history[delta] = DayHistory(self.last_commit.date, self.last_commit.loc_for_type)

        tmp = list(self.last_commit.loc_for_type)
        self.last_commit = Commit()
        self.last_commit.loc_for_type = tmp

    def run(self):
        nnn = 0
        for x in gitlog():
            nnn += 1
            if x.startswith('commit'):
                self.pop()
                self.last_commit.hsh = x[7:14]

            if x.startswith('Author'):
                self.last_commit.who = x.replace("Author: ", '').replace('\n', '')
                self.last_commit.who = re.sub(">.*", "", self.last_commit.who)
                self.last_commit.who = re.sub(".*<", "", self.last_commit.who)

            if x.startswith('Date'):
                self.fc = 1
                self.last_commit.date = datetime(*parsedate(x[5:])[:7])

            if self.fc == 2:
                self.last_commit.cmt = x[:-1]
                self.fc = 0

            if self.fc == 1:
                if len(x) == 1:
                    self.fc = 2

            if x.startswith('+++'):
                self.file_type_ppp = filetype(x)

            if x.startswith('---'):
                self.file_type_mmm = filetype(x)

            if x.startswith('+') and not x.startswith('+++'):
                self.last_commit.increment_loc(self.file_type_ppp)
                if self.file_type_ppp <FileTypes.PYAPI:
                    self.locs += 1

            if x.startswith('-') and not x.startswith('---'):
                self.last_commit.decrement_loc(self.file_type_mmm)
                if self.file_type_mmm < FileTypes.PYAPI:
                    self.locs -= 1

            # if nnn>1000000:
            #     break

        self.pop()

    def save_report(self, filename):
        print("Saving report in {0}".format(filename))
        with open(filename, 'w') as the_file:
            for key in self.days_history:
                dayhist = self.days_history[key]
                pstr = "%s %s \n" % (str(dayhist.date), ' '.join(str(e) for e in dayhist.loc_for_type))
                the_file.write(pstr)
