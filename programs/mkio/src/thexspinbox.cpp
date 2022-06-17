/*
 * Copyright 2022 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "thexspinbox.h"
#include "baseitem.h"

THexSpinBox::THexSpinBox(QWidget *parent) : QSpinBox(parent)
{
    setPrefix("0x");
    setDisplayIntegerBase(16);
    setRange(0, MAX_INPUT_VALUE);
}
//---------------------------------------------------------------------------
QString THexSpinBox::textFromValue(int value) const
{
    return QString::number(value, 16).toUpper();
}
//---------------------------------------------------------------------------
int THexSpinBox::valueFromText(const QString &text) const
{
    return text.toInt(0, 16);
}
//---------------------------------------------------------------------------
QValidator::State THexSpinBox::validate(QString &input, int &pos) const
{
    QString copy(input);
    if (copy.startsWith("0x"))
        copy.remove(0, 2);
    pos -= copy.size() - copy.trimmed().size();
    copy = copy.trimmed();
    if (copy.isEmpty())
        return QValidator::Intermediate;
    input = QString("0x") + copy.toUpper();
    bool okay;
    int val = copy.toUInt(&okay, 16);
    if (!okay || val > MAX_INPUT_VALUE)
    {
       return QValidator::Invalid;
    }
    return QValidator::Acceptable;
}
