#include "tbinaryspinbox.h"
#include "baseitem.h"

TBinarySpinBox::TBinarySpinBox(QWidget *parent) : QSpinBox(parent)
{
   setRange(0, MAX_INPUT_VALUE);
}
//---------------------------------------------------------------------------
QString TBinarySpinBox::textFromValue(int value) const
{
    return QString::number(value, 2);
}
//---------------------------------------------------------------------------
int TBinarySpinBox::valueFromText(const QString &text) const
{
    return text.toInt(0, 2);
}
//---------------------------------------------------------------------------
QValidator::State TBinarySpinBox::validate(QString& input, int&) const
{
    bool okay;
    int val = input.toUInt(&okay, 2);
    if ((!okay || val > MAX_INPUT_VALUE) && (input.size() != 0))
    {
        return QValidator::Invalid;
    }
    return QValidator::Acceptable;
}

