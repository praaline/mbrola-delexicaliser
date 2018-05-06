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

#include "AnnotationElement.h"

namespace Praaline {
namespace Core {

AnnotationElement::AnnotationElement()
{
    m_isNew = true;
    m_isDirty = true;
}

AnnotationElement::AnnotationElement(const QString &text) :
    m_text(text)
{
    m_isNew = true;
    m_isDirty = true;
}

AnnotationElement::AnnotationElement(const QString &text, const QHash<QString, QVariant> &attributes) :
    m_text(text), m_attributes(attributes)
{
    m_isNew = true;
    m_isDirty = true;
}

AnnotationElement::AnnotationElement(const AnnotationElement &other) :
    m_text(other.m_text), m_attributes(other.m_attributes)
{
    m_isNew = true;
    m_isDirty = true;
}

} // namespace Core
} // namespace Praaline
