#include "suncalculationsdialog.h"
#include "ui_suncalculationsdialog.h"

SunCalculationsDialog::SunCalculationsDialog(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::SunCalculationsDialog)
{
    m_ui->setupUi(this);

    // Get local coordinates from settings
    QSettings settings;

    settings.beginGroup("position");
    m_latitude.setTotalDegree(settings.value("latitude").toDouble());
    if (settings.value("latitudeDirection").toString() == "S")
    {
        m_latitude.setTotalDegree(0.00 - m_latitude.getTotalDegree());
    }

    settings.endGroup();

    // Equation of time chart
    QLineSeries *serie0 = new QLineSeries();

    for (int i = 1; i <= 365; i++) {
        double B = (2 * PI / 365) * (i - 81);
        QPointF p((qreal) i, 9.87 * sin(2 * B) - 7.53 * cos(B) - 1.5 * sin(B));
        *serie0 << p;
    }

    QValueAxis *axisY0 = new QValueAxis();
    axisY0->setRange(-20, 20);

    QValueAxis *axisX0 = new QValueAxis();
    axisX0->setRange(0, 365);

    QChart *chart = new QChart();
    chart->setTitle("Equation du temps");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();
    chart->addSeries(serie0);
    chart->addAxis(axisY0, Qt::AlignLeft);
    serie0->attachAxis(axisY0);
    chart->addAxis(axisX0, Qt::AlignBottom);
    serie0->attachAxis(axisX0);

    m_chartView = new QChartView(chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    m_ui->sunPositionGroupBox->layout()->addWidget(m_chartView);

    // First calculation
    ComputeSunPosition();
}

SunCalculationsDialog::~SunCalculationsDialog()
{
    delete m_ui;
}


void SunCalculationsDialog::ComputeSunPosition()
{
    // Number of days from 01/01
    int dayCount[12] = {0,31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    unsigned int days = dayCount[m_ui->monthComboBox->currentIndex()] + m_ui->daySpinBox->value();

    // Compute declination angle
    Angle delta(23.45 * sin((2 * PI / 365) * (days + 284)));

    // Compute elevation
    Angle elevation(m_latitude.getTotalDegree() + delta.getTotalDegree());

    m_ui->elevationLineEdit->setText(QString::number(elevation.getTotalDegree()) + "°");
    m_ui->sunriseLineEdit->setText("");
    m_ui->sunsetLineEdit->setText("");
}


void SunCalculationsDialog::on_monthComboBox_currentIndexChanged(int index)
{
    // Set day maximum according to month
    switch(index)
    {
    case 1:  // February
        m_ui->daySpinBox->setMaximum(28);
        break;
    case 0:  // January
    case 2:  // March
    case 4:  // May
    case 6:  // July
    case 7:  // Aout
    case 9:  // October
    case 12: // December
        m_ui->daySpinBox->setMaximum(31);
        break;
    case 3:  // April
    case 5:  // June
    case 8:  // September
    case 10: // November
        m_ui->daySpinBox->setMaximum(30);
        break;
    }

    // Update values
    ComputeSunPosition();
}


void SunCalculationsDialog::on_daySpinBox_valueChanged(int arg1)
{
    // Update values
    ComputeSunPosition();
}

