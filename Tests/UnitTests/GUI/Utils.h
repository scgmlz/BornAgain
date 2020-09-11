// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/UnitTests/GUI/Utils.h
//! @brief     Defines auxiliary test functions in a namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_UNITTESTS_GUI_UTILS_H
#define BORNAGAIN_TESTS_UNITTESTS_GUI_UTILS_H

#include "GUI/coregui/Models/PropertyItem.h"
#include "GUI/coregui/Models/SessionXML.h"
#include <QString>
#include <QXmlStreamWriter>

template <class T> class OutputData;
class RealDataItem;

namespace GuiUnittestUtils
{
enum class DIM { D1 = 1, D2 = 2 };

//! Creates directory in current working directory. If such directory already exists,
//! it will be removed with all its content.
void create_dir(const QString& dir_name);

//! Creates output data array for testing purposes
std::unique_ptr<OutputData<double>> createData(double value = 0.0, DIM n_dim = DIM::D2);

//! Creates real data item initialized with OutputData for testing purposes
RealDataItem* createRealData(const QString& name, SessionModel& model, double value = 0.0,
                             DIM n_dim = DIM::D2);

//! Converts property to XML string
template <typename T> QString propertyToXML(const T& property)
{
    QString result;
    QXmlStreamWriter writer(&result);
    SessionXML::writeVariant(&writer, property.variant(), /*role*/ 0);
    return result;
}

//! Converts XML string to property
template <typename T> T propertyFromXML(const QString& buffer)
{
    std::unique_ptr<PropertyItem> item(new PropertyItem);
    QXmlStreamReader reader(buffer);

    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (reader.name() == SessionXML::ParameterTag) {
                SessionXML::readProperty(&reader, item.get());
            }
        }
    }

    return item->value().value<T>();
}

//! Helper function to test if data are the same.
bool isTheSame(const OutputData<double>& data1, const OutputData<double>& data2);

//! Helper function to check if file on disk represents same data.
bool isTheSame(const QString& fileName, const OutputData<double>& data);

} // namespace GuiUnittestUtils

#endif // BORNAGAIN_TESTS_UNITTESTS_GUI_UTILS_H
