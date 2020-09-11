#!/usr/bin/env python3

'''
To be used only once: convert performance log from legacy format to YAML
'''

import datetime, re, sys, pytz, yaml
from collections import OrderedDict
from pytz import timezone

################################################################################
# Improved YAML dumper, to write dicts and lists in nice form
################################################################################

class FlowSeq( list ): pass

# The improved YAML dumper

def improved_dump(data, stream=None, Dumper=yaml.Dumper, **kwds):
    class ImprovedDumper(Dumper):
        pass
    def odict_representer(dumper, data):
        return dumper.represent_mapping(
            yaml.resolver.BaseResolver.DEFAULT_MAPPING_TAG,
            data.items())
    def flowseq_representer(dumper, data):
        return dumper.represent_sequence(
            yaml.resolver.BaseResolver.DEFAULT_SEQUENCE_TAG,
            data,
            flow_style=True )
    ImprovedDumper.add_representer(OrderedDict, odict_representer)
    ImprovedDumper.add_representer(FlowSeq, flowseq_representer)
    return yaml.dump(data, stream, ImprovedDumper,
                     allow_unicode=True, encoding='utf-8',
                     default_flow_style=False, indent=4, width=70, **kwds)

# Just for documentation, not used here: the corresponding loader.

def improved_load(stream, Loader=yaml.Loader, object_pairs_hook=OrderedDict):
    class ImprovedLoader(Loader):
        pass
    def construct_mapping(loader, node):
        loader.flatten_mapping(node)
        return object_pairs_hook(loader.construct_pairs(node))
    ImprovedLoader.add_constructor(
        yaml.resolver.BaseResolver.DEFAULT_MAPPING_TAG,
        construct_mapping)
    return yaml.load(stream, ImprovedLoader)

################################################################################
# Time conversion
################################################################################

garching = timezone('Europe/Berlin')
def nice_datetime( dt ):
    rounded = dt - datetime.timedelta(microseconds=dt.microsecond)
    return garching.localize(rounded).isoformat()

################################################################################
# Standarized blocks
################################################################################

def coder(value, offset_coder, offset, precision):
    ret = OrderedDict()
    ret['value'] = value
    ret['offset_coder'] = offset_coder
    ret['offset'] = offset
    ret['precision'] = precision
    return ret

def scan(j):
    ret = OrderedDict()
    ret['scan_parameters'] = OrderedDict()
    ret['scan_parameters']['omgs'] = 0.1*j
    ret['time'] = 2.02
    ret['monitor'] = random.randint(10000, 40000)
    ret['image'] = "img%04i" % j
    return ret

################################################################################
# Main
################################################################################

o = []

fni = 'partial_history.txt'
fno = 'performance_log2.yaml'
fd = open( fni, 'r' )
ti = fd.read()
fd.close()

aa = re.split( r'\n\s*?\n', ti )
for a in aa: # block
    bb = re.split( r'\n', a.rstrip() )
    m = re.match( r'#\s*(.*)', bb[0] )
    if not m:
        raise "block header not found"
    comment = m.group(1)
    # print("### "+comment[0:20]+" --> %i" %( len(bb)-2 ) )
    header = re.split( r'\s*\|\s*', bb[1] )[1:-1]
    if header[0]!="date":
        raise "unexpected block header"
    nentry = len(header)
    outcome = []
    for b in bb[2:]:
        c = re.split( r'\s*\|\s*', b )[1:-1]
        # print("'"+b+"'")
        if len(c)!=len(header):
            raise "wrong number of records"
        result = OrderedDict()
        for i in range(len(header)):
            out = c[i]
            if header[i]=="tr":
                out = int(out)
            elif i>3:
                out = float(out)
            result[header[i]] = out
        outcome.append( result )
    entry = OrderedDict()
    entry['version'] = comment
    entry['outcome'] = outcome
    o.append( entry )

yaml_str = improved_dump( o )
fd = open( fno, 'wb' )
fd.write( yaml_str )
fd.close()
