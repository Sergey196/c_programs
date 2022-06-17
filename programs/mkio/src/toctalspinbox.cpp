#include "toctalspinbox.h"
#include "baseitem.h"

TOctalSpinBox::TOctalSpinBox(QWidget *parent): QSpinBox(parent)
{
   setRange(0, MAX_INPUT_VALUE);
}
//---------------------------------------------------------------------------
QString TOctalSpinBox::textFromValue(int value) const
{
    return QString::number(value, 8);
}
//---------------------------------------------------------------------------
int TOctalSpinBox::valueFromText(const QString &text) const
{
    return text.toInt(0, 8);
}
//---------------------------------------------------------------------------
QValidator::State TOctalSpinBox::validate(QString& input, int&) const
{
    bool okay;
    int val = input.toUInt(&okay, 8);
    if ((!okay || val > MAX_INPUT_VALUE) && (input.size() != 0))
    {
        return QValidator::Invalid;
    }
    return QValidator::Acceptable;
}
