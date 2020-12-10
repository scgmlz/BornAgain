//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTranslators.h
//! @brief     Defines interface IParameterTranslator and subclasses
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_PARAMETERTRANSLATORS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_PARAMETERTRANSLATORS_H

#include <QStringList>

class SessionItem;

class IPathTranslator {
public:
    virtual ~IPathTranslator();

    virtual IPathTranslator* clone() const = 0;

    virtual QStringList translate(const QStringList& list) const = 0;
};

class ModelTypeTranslator : public IPathTranslator {
public:
    ModelTypeTranslator(QString gui_model_type, QString domain_name);
    ~ModelTypeTranslator() override {}

    ModelTypeTranslator* clone() const override;

    QStringList translate(const QStringList& list) const override;

private:
    QString m_gui_model_type;
    QString m_domain_name;
};

class AddElementTranslator : public IPathTranslator {
public:
    AddElementTranslator(QString gui_name, QString additional_name);
    ~AddElementTranslator() override {}

    AddElementTranslator* clone() const override;

    QStringList translate(const QStringList& list) const override;

private:
    QString m_gui_name;
    QString m_additional_name;
};

class RotationTranslator : public IPathTranslator {
public:
    ~RotationTranslator() override {}

    RotationTranslator* clone() const override { return new RotationTranslator; }

    QStringList translate(const QStringList& list) const override;
};

class DistributionNoneTranslator : public IPathTranslator {
public:
    ~DistributionNoneTranslator() override {}

    DistributionNoneTranslator* clone() const override { return new DistributionNoneTranslator; }

    QStringList translate(const QStringList& list) const override;
};

class RoughnessTranslator : public IPathTranslator {
public:
    RoughnessTranslator(const SessionItem* p_parent);
    ~RoughnessTranslator() override {}

    RoughnessTranslator* clone() const override;

    QStringList translate(const QStringList& list) const override;

private:
    int getLayerIndex(QString layerName) const;
    int numberOfLayers() const;
    const SessionItem* m_parent;
};

class VectorParameterTranslator : public IPathTranslator {
public:
    VectorParameterTranslator(QString gui_name, std::string base_name,
                              QStringList additional_names = {});
    ~VectorParameterTranslator() override {}

    VectorParameterTranslator* clone() const override;

    QStringList translate(const QStringList& list) const override;

private:
    QString m_gui_name;
    std::string m_base_name;
    QStringList m_additional_names;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_PARAMETERTRANSLATORS_H
