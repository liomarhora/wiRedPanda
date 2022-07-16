// Copyright 2015 - 2022, GIBIS-Unifesp and the WiRedPanda contributors
// SPDX-License-Identifier: GPL-3.0-or-later

#include "inputbutton.h"

#include "globalproperties.h"
#include "qneport.h"

#include <QGraphicsSceneMouseEvent>

namespace
{
int id = qRegisterMetaType<InputButton>();
}

InputButton::InputButton(QGraphicsItem *parent)
    : GraphicElementInput(ElementType::InputButton, ElementGroup::Input, ":/input/buttonOff.svg", tr("<b>PUSH BUTTON</b>"), tr("Button"), 0, 0, 1, 1, parent)
{
    if (GlobalProperties::skipInit) {
        return;
    }

    m_defaultSkins = QStringList{
        ":/input/buttonOff.svg",
        ":/input/buttonOn.svg",
    };
    m_alternativeSkins = m_defaultSkins;
    setPixmap(0);

    m_locked = false;
    setCanChangeSkin(true);
    setRotatable(false);
    InputButton::setOff();
    setHasLabel(true);
    setHasTrigger(true);
    setPortName(m_translatedName);
    setToolTip(m_translatedName);
}

void InputButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers().testFlag(Qt::ControlModifier)) {
        return;
    }

    if (!m_locked && (event->button() == Qt::LeftButton)) {
        setOn();
        event->accept();
    }

    QGraphicsItem::mousePressEvent(event);
}

void InputButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (!m_locked && (event->button() == Qt::LeftButton)) {
        setOff();
        event->accept();
    }

    GraphicElement::mouseReleaseEvent(event);
}

void InputButton::save(QDataStream &stream) const
{
    GraphicElement::save(stream);
    stream << m_locked;
}

void InputButton::load(QDataStream &stream, QMap<quint64, QNEPort *> &portMap, const double version)
{
    GraphicElement::load(stream, portMap, version);

    if (version >= 3.1) {
        stream >> m_locked;
    }
}

bool InputButton::isOn(const int port) const
{
    Q_UNUSED(port);
    return m_isOn;
}

void InputButton::setOff()
{
    InputButton::setOn(false);
}

void InputButton::setOn()
{
    InputButton::setOn(true);
}

void InputButton::setOn(const bool value, const int port)
{
    Q_UNUSED(port);

    m_isOn = value;
    setPixmap(static_cast<int>(m_isOn));
    outputPort()->setStatus(static_cast<Status>(m_isOn));
}

void InputButton::setSkin(const bool defaultSkin, const QString &fileName)
{
    if (defaultSkin) {
        m_alternativeSkins = m_defaultSkins;
    } else {
        m_alternativeSkins[static_cast<int>(m_isOn)] = fileName;
    }

    m_usingDefaultSkin = defaultSkin;
    setPixmap(static_cast<int>(m_isOn));
}
