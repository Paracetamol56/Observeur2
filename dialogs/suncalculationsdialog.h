#ifndef SUNCALCULATIONSDIALOG_H
#define SUNCALCULATIONSDIALOG_H

#include <QWidget>
#include <QSettings>
#include <QDebug>
#include <math.h>

#include <QChart>
#include <QChartView>
#include <QValueAxis>
#include <QPainter>
#include <QLineSeries>

#include "angleutilities/angle.h"

namespace Ui {
class SunCalculationsDialog;
}

class SunCalculationsDialog : public QWidget
{
    Q_OBJECT

private:
    Ui::SunCalculationsDialog *m_ui;

    Angle m_latitude = Angle(0.0);

    // Chart
    QChartView *m_chartView;

public:
    explicit SunCalculationsDialog(QWidget *parent = nullptr);
    ~SunCalculationsDialog();

private:
    void ComputeSunPosition();


private slots:
    void on_monthComboBox_currentIndexChanged(int index);
    void on_daySpinBox_valueChanged(int arg1);
};

#endif // SUNCALCULATIONSDIALOG_H
