/*
    Praaline - Core module - Annotation
    Copyright (c) 2011-2018 George Christodoulides

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#include <QString>
#include <QList>
#include <QHash>
#include "AnnotationTier.h"

namespace Praaline {
namespace Core {

QString AnnotationTier::name() const
{
    return m_name;
}

void AnnotationTier::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

RealTime AnnotationTier::tMin() const
{
    return m_tMin;
}

RealTime AnnotationTier::tMax() const
{
    return m_tMax;
}

RealTime AnnotationTier::duration() const
{
    return m_tMax - m_tMin;
}

} // namespace Core
} // namespace Praaline
