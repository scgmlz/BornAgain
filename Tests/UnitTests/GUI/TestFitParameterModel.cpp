#include "GUI/coregui/Models/FitParameterItems.h"
#include "GUI/coregui/Models/FitParameterProxyModel.h"
#include "GUI/coregui/Models/FitSuiteItem.h"
#include "GUI/coregui/Models/JobModel.h"
#include "Tests/GTestWrapper/google_test.h"

class TestFitParameterModel : public ::testing::Test
{
};

TEST_F(TestFitParameterModel, test_InitialState)
{
    JobModel source;
    SessionItem* fitSuiteItem = source.insertNewItem("FitSuite");
    SessionItem* container = source.insertNewItem("FitParameterContainer", fitSuiteItem->index(),
                                                  -1, FitSuiteItem::T_FIT_PARAMETERS_CONTAINER);
    FitParameterProxyModel proxy(dynamic_cast<FitParameterContainerItem*>(container));

    EXPECT_EQ(0, proxy.rowCount(QModelIndex()));
    EXPECT_EQ(static_cast<int>(FitParameterProxyModel::MAX_COLUMNS),
              proxy.columnCount(QModelIndex()));
    EXPECT_EQ(container, proxy.itemForIndex(QModelIndex()));
}

TEST_F(TestFitParameterModel, test_addFitParameter)
{
    JobModel source;
    SessionItem* fitSuiteItem = source.insertNewItem("FitSuite");
    SessionItem* container = source.insertNewItem("FitParameterContainer", fitSuiteItem->index(),
                                                  -1, FitSuiteItem::T_FIT_PARAMETERS_CONTAINER);
    FitParameterProxyModel proxy(dynamic_cast<FitParameterContainerItem*>(container));

    // adding fit parameter
    SessionItem* fitPar0 = source.insertNewItem("FitParameter", container->index());
    fitPar0->setDisplayName("par");
    fitPar0->setItemValue(FitParameterItem::P_MIN, 1.0);
    fitPar0->setItemValue(FitParameterItem::P_MAX, 2.0);
    fitPar0->setItemValue(FitParameterItem::P_START_VALUE, 3.0);

    // checking index of root
    EXPECT_EQ(1, proxy.rowCount(QModelIndex()));
    EXPECT_EQ(FitParameterProxyModel::MAX_COLUMNS, proxy.columnCount(QModelIndex()));

    // accessing item at col=0 (original FitParameterItem)
    QModelIndex index = proxy.index(0, 0, QModelIndex());
    EXPECT_EQ(index.row(), 0);
    EXPECT_EQ(index.column(), 0);
    EXPECT_EQ(proxy.rowCount(index), 0);
    EXPECT_EQ(proxy.columnCount(index), 0); // non existing linkItem

    EXPECT_EQ(fitPar0, proxy.itemForIndex(index));
    EXPECT_EQ(fitPar0->displayName(), proxy.data(index).toString());
    EXPECT_EQ(index, proxy.indexOfItem(fitPar0));

    // accessing item at col=2
    index = proxy.index(0, FitParameterProxyModel::PAR_MIN, QModelIndex());
    EXPECT_EQ(index.row(), 0);
    EXPECT_EQ(index.column(), FitParameterProxyModel::PAR_MIN);
    EXPECT_EQ(proxy.rowCount(index), 0);
    EXPECT_EQ(proxy.columnCount(index), 0);

    EXPECT_EQ(fitPar0->getItem(FitParameterItem::P_MIN), proxy.itemForIndex(index));
    EXPECT_EQ(fitPar0->getItemValue(FitParameterItem::P_MIN).toDouble(),
              proxy.data(index).toDouble());
    EXPECT_EQ(index, proxy.indexOfItem(fitPar0->getItem(FitParameterItem::P_MIN)));

    // accessing item at col=3
    index = proxy.index(0, FitParameterProxyModel::PAR_VALUE, QModelIndex());
    EXPECT_EQ(index.row(), 0);
    EXPECT_EQ(index.column(), FitParameterProxyModel::PAR_VALUE);
    EXPECT_EQ(proxy.rowCount(index), 0);
    EXPECT_EQ(proxy.columnCount(index), 0);

    EXPECT_EQ(fitPar0->getItem(FitParameterItem::P_START_VALUE), proxy.itemForIndex(index));
    EXPECT_EQ(fitPar0->getItemValue(FitParameterItem::P_START_VALUE).toDouble(),
              proxy.data(index).toDouble());
    EXPECT_EQ(index, proxy.indexOfItem(fitPar0->getItem(FitParameterItem::P_START_VALUE)));

    // accessing item at col=4
    index = proxy.index(0, FitParameterProxyModel::PAR_MAX, QModelIndex());
    EXPECT_EQ(index.row(), 0);
    EXPECT_EQ(index.column(), FitParameterProxyModel::PAR_MAX);
    EXPECT_EQ(proxy.rowCount(index), 0);
    EXPECT_EQ(proxy.columnCount(index), 0);

    EXPECT_EQ(fitPar0->getItem(FitParameterItem::P_MAX), proxy.itemForIndex(index));
    EXPECT_EQ(fitPar0->getItemValue(FitParameterItem::P_MAX).toDouble(),
              proxy.data(index).toDouble());
    EXPECT_EQ(index, proxy.indexOfItem(fitPar0->getItem(FitParameterItem::P_MAX)));

    // ----------------------------------------------------
    // adding second fit parameter
    // ----------------------------------------------------
    SessionItem* fitPar1 = source.insertNewItem("FitParameter", container->index());
    fitPar0->setDisplayName("par");
    fitPar0->setItemValue(FitParameterItem::P_MIN, 10.0);
    fitPar0->setItemValue(FitParameterItem::P_MAX, 20.0);
    fitPar0->setItemValue(FitParameterItem::P_START_VALUE, 30.0);

    // checking index of root
    EXPECT_EQ(2, proxy.rowCount(QModelIndex()));
    EXPECT_EQ(FitParameterProxyModel::MAX_COLUMNS, proxy.columnCount(QModelIndex()));

    // accessing item at col=3 for fitPar0
    index = proxy.index(0, FitParameterProxyModel::PAR_VALUE, QModelIndex());
    EXPECT_EQ(index.row(), 0);
    EXPECT_EQ(index.column(), FitParameterProxyModel::PAR_VALUE);
    EXPECT_EQ(proxy.rowCount(index), 0);
    EXPECT_EQ(proxy.columnCount(index), 0);

    EXPECT_EQ(fitPar0->getItem(FitParameterItem::P_START_VALUE), proxy.itemForIndex(index));
    EXPECT_EQ(fitPar0->getItemValue(FitParameterItem::P_START_VALUE).toDouble(),
              proxy.data(index).toDouble());
    EXPECT_EQ(index, proxy.indexOfItem(fitPar0->getItem(FitParameterItem::P_START_VALUE)));

    // accessing item at col=3 for fitPar1
    index = proxy.index(1, FitParameterProxyModel::PAR_VALUE, QModelIndex());
    EXPECT_EQ(index.row(), 1);
    EXPECT_EQ(index.column(), FitParameterProxyModel::PAR_VALUE);
    EXPECT_EQ(proxy.rowCount(index), 0);
    EXPECT_EQ(proxy.columnCount(index), 0);

    EXPECT_EQ(fitPar1->getItem(FitParameterItem::P_START_VALUE), proxy.itemForIndex(index));
    EXPECT_EQ(fitPar1->getItemValue(FitParameterItem::P_START_VALUE).toDouble(),
              proxy.data(index).toDouble());
    EXPECT_EQ(index, proxy.indexOfItem(fitPar1->getItem(FitParameterItem::P_START_VALUE)));
}

TEST_F(TestFitParameterModel, test_addFitParameterAndLink)
{
    JobModel source;
    SessionItem* fitSuiteItem = source.insertNewItem("FitSuite");
    SessionItem* container = source.insertNewItem("FitParameterContainer", fitSuiteItem->index(),
                                                  -1, FitSuiteItem::T_FIT_PARAMETERS_CONTAINER);
    FitParameterProxyModel proxy(dynamic_cast<FitParameterContainerItem*>(container));

    // adding fit parameter
    SessionItem* fitPar0 = source.insertNewItem("FitParameter", container->index());
    fitPar0->setDisplayName("par");
    fitPar0->setItemValue(FitParameterItem::P_MIN, 1.0);
    fitPar0->setItemValue(FitParameterItem::P_MAX, 2.0);
    fitPar0->setItemValue(FitParameterItem::P_START_VALUE, 3.0);

    // adding link
    SessionItem* link0 = source.insertNewItem("FitParameterLink", fitPar0->index());
    link0->setItemValue(FitParameterLinkItem::P_LINK, "link0");

    // checking index of root
    EXPECT_EQ(1, proxy.rowCount(QModelIndex()));
    EXPECT_EQ(FitParameterProxyModel::MAX_COLUMNS, proxy.columnCount(QModelIndex()));

    // accessing item at col=0 (original FitParameterItem)
    QModelIndex index = proxy.index(0, 0, QModelIndex());
    EXPECT_EQ(index.row(), 0);
    EXPECT_EQ(index.column(), 0);
    EXPECT_EQ(proxy.rowCount(index), 1);
    EXPECT_EQ(proxy.columnCount(index), 1); // linkItem

    // testing link0 index
    QModelIndex linkIndex = proxy.index(0, 0, index);
    EXPECT_EQ(linkIndex.row(), 0);
    EXPECT_EQ(linkIndex.column(), 0);
    EXPECT_EQ(linkIndex.parent(), index);
    EXPECT_EQ(proxy.rowCount(linkIndex), 0);
    EXPECT_EQ(proxy.columnCount(linkIndex), 0);

    EXPECT_EQ(proxy.parent(linkIndex), index);
    EXPECT_EQ(proxy.itemForIndex(linkIndex), link0->getItem(FitParameterLinkItem::P_LINK));

    EXPECT_EQ(link0->getItemValue(FitParameterLinkItem::P_LINK).toString(),
              proxy.data(linkIndex).toString());
    EXPECT_EQ(linkIndex, proxy.indexOfItem(link0->getItem(FitParameterLinkItem::P_LINK)));

    // adding second link
    SessionItem* link1 = source.insertNewItem("FitParameterLink", fitPar0->index());
    link1->setItemValue(FitParameterLinkItem::P_LINK, "link1");
    EXPECT_EQ(proxy.rowCount(index), 2);
    EXPECT_EQ(proxy.columnCount(index), 1); // linkItem

    linkIndex = proxy.index(1, 0, index);
    EXPECT_EQ(linkIndex.row(), 1);
    EXPECT_EQ(linkIndex.column(), 0);
    EXPECT_EQ(linkIndex.parent(), index);
    EXPECT_EQ(proxy.rowCount(linkIndex), 0);
    EXPECT_EQ(proxy.columnCount(linkIndex), 0);
    EXPECT_EQ(proxy.parent(linkIndex), index);

    EXPECT_EQ(proxy.parent(linkIndex), index);
    EXPECT_EQ(proxy.itemForIndex(linkIndex), link1->getItem(FitParameterLinkItem::P_LINK));
}

TEST_F(TestFitParameterModel, test_addTwoFitParameterAndLinks)
{
    JobModel source;
    SessionItem* fitSuiteItem = source.insertNewItem("FitSuite");
    SessionItem* container = source.insertNewItem("FitParameterContainer", fitSuiteItem->index(),
                                                  -1, FitSuiteItem::T_FIT_PARAMETERS_CONTAINER);
    FitParameterProxyModel proxy(dynamic_cast<FitParameterContainerItem*>(container));

    // adding fit parameters
    SessionItem* fitPar0 = source.insertNewItem("FitParameter", container->index());
    SessionItem* link0 = source.insertNewItem("FitParameterLink", fitPar0->index());
    Q_UNUSED(link0);

    SessionItem* fitPar1 = source.insertNewItem("FitParameter", container->index());
    SessionItem* link1 = source.insertNewItem("FitParameterLink", fitPar1->index());
    Q_UNUSED(link1);

    // checking index of root
    EXPECT_EQ(2, proxy.rowCount(QModelIndex()));
    EXPECT_EQ(FitParameterProxyModel::MAX_COLUMNS, proxy.columnCount(QModelIndex()));

    // accessing fitPar1
    QModelIndex index1 = proxy.index(1, 0, QModelIndex());
    EXPECT_EQ(index1.row(), 1);
    EXPECT_EQ(index1.column(), 0);
    EXPECT_EQ(index1.parent(), QModelIndex());
    EXPECT_EQ(proxy.rowCount(index1), 1);
    EXPECT_EQ(proxy.columnCount(index1), 1);

    EXPECT_EQ(fitPar1, proxy.itemForIndex(index1));
    EXPECT_EQ(fitPar1->displayName(), proxy.data(index1).toString());
    EXPECT_EQ(index1, proxy.indexOfItem(fitPar1));

    // accessing link1
    QModelIndex linkIndex1 = proxy.index(0, 0, index1);
    EXPECT_EQ(linkIndex1.row(), 0);
    EXPECT_EQ(linkIndex1.column(), 0);
    EXPECT_EQ(linkIndex1.parent(), index1);
    EXPECT_EQ(proxy.rowCount(linkIndex1), 0);
    EXPECT_EQ(proxy.columnCount(linkIndex1), 0);
}
