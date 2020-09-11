#include "Tests/UnitTests/GUI/Comparators.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Views/MaterialEditor/ExternalProperty.h"
#include <QMetaType>

bool Comparators::m_is_registered = false;

void Comparators::registerComparators()
{
    QMetaType::registerComparators<ComboProperty>();
    QMetaType::registerComparators<ExternalProperty>();
    m_is_registered = true;
}

bool Comparators::registered()
{
    return m_is_registered;
}
