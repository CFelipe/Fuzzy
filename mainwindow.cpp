#include "mainwindow.h"
#include "qcustomplot.h"

QWidget* MainWindow::createEntry() {
    QWidget* entry = new QWidget;
    entry->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QGridLayout* entryLayout = new QGridLayout;
    entryLayout->setColumnStretch(0, 1);
    entryLayout->setColumnStretch(1, 1);
    QLineEdit* titleInput = new QLineEdit;
    titleInput->setPlaceholderText(tr("Título"));
    QComboBox* curveBox = new QComboBox();
    curveBox->addItem("Trapezoidal");
    curveBox->addItem("Triangular");
    QWidget* paramsForm = new QWidget;
    QFormLayout* paramsFormLayout = new QFormLayout;

    QLineEdit* p1 = new QLineEdit;
    QLineEdit* p2 = new QLineEdit;
    QLineEdit* p3 = new QLineEdit;
    paramsFormLayout->addRow("α<sub>min</sub>",	p1);
    paramsFormLayout->addRow("β", 			p2);
    paramsFormLayout->addRow("α<sub>max</sub>",	p3);
    paramsFormLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    paramsForm->setLayout(paramsFormLayout);
    paramsForm->setForegroundRole(QPalette::Dark);
    paramsForm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    paramsFormLayout->setContentsMargins(0, 0, 0, 0);
    //paramsForm->setStyleSheet("border: 1px solid green");

    QPushButton* removeButton = new QPushButton(tr("Remover"));

    QCustomPlot* customPlot = new QCustomPlot(this);
    //customPlot->xAxis->setVisible(false);
    //customPlot->yAxis->setVisible(false);
    QVector<double> yTickVector;
    customPlot->axisRect()->setAutoMargins(QCP::msNone);
    customPlot->axisRect()->setMargins(QMargins(5,5,5,5));

    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);
    customPlot->replot();

    entryLayout->addWidget(titleInput, 0, 0);
    entryLayout->addWidget(curveBox, 	0, 1);
    entryLayout->addWidget(paramsForm, 1, 0, 4, 1);
    entryLayout->addWidget(customPlot, 1, 1, 4, 1);
    entryLayout->addWidget(removeButton, 5, 0, 1, 2);
    entry->setLayout(entryLayout);
    entryLayout->setContentsMargins(0, 0, 0, 0);
    //entry->setStyleSheet("border: 1px solid red");

    return entry;
}

QWidget* MainWindow::createRules() {
    QWidget* ruleWidget = new QWidget;
    QGridLayout* ruleLayout = new QGridLayout;
    ruleLayout->setAlignment(Qt::AlignTop);
    QLabel* label1 = new QLabel;
    QComboBox* combo1 = new QComboBox;
    QPushButton* push1 = new QPushButton;
    push1->setText(tr("-"));
    label1->setText(tr("<b>IF</b>"));
    label1->setStyleSheet("padding-top: 3px");
    label1->setAlignment(Qt::AlignRight);
    combo1->addItem("Gordo");
    combo1->addItem("Magro");
    QLabel* label2 = new QLabel;
    QComboBox* combo2 = new QComboBox;
    QPushButton* push2 = new QPushButton;
    push2->setText(tr("+"));
    label2->setAlignment(Qt::AlignRight);
    label2->setText(tr("<b>AND</b>"));
    label2->setStyleSheet("padding-top: 3px");
    combo2->addItem("Velho");
    combo2->addItem("Novo");
    QLabel* label3 = new QLabel;
    QComboBox* combo3 = new QComboBox;
    QPushButton* push3 = new QPushButton;
    push3->setText(tr("+"));
    label3->setAlignment(Qt::AlignRight);
    label3->setText(tr("<b>THEN</b>"));
    label3->setStyleSheet("padding-top: 3px");
    combo3->addItem("Velho");
    combo3->addItem("Novo");

    ruleWidget->setLayout(ruleLayout);
    ruleLayout->addWidget(label1, 0, 0);
    ruleLayout->addWidget(combo1, 0, 1);
    ruleLayout->addWidget(push1, 0, 2);
    ruleLayout->addWidget(label2, 1, 0);
    ruleLayout->addWidget(combo2, 1, 1);
    ruleLayout->addWidget(push2, 1, 2);
    ruleLayout->addWidget(label3, 2, 0);
    ruleLayout->addWidget(combo3, 2, 1);
    ruleLayout->addWidget(push3, 2, 2);

    ruleLayout->setColumnStretch(0, 0);
    ruleLayout->setColumnStretch(1, 1);
    ruleLayout->setColumnStretch(2, 0);

    return ruleWidget;
}


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QLayout* mainLayout = new QHBoxLayout;

    QScrollArea* entriesScroll = new QScrollArea;
    QWidget* entries = new QWidget;
    //entries->setStyleSheet("border: 1px solid blue");
    QLayout* entriesLayout = new QVBoxLayout;
    entriesLayout->setAlignment(Qt::AlignTop);

    QWidget* entry1 = createEntry();
    QWidget* entry2 = createEntry();
    QWidget* rules = createRules();
    QFrame* separator = new QFrame;
    separator->setFrameStyle(QFrame::HLine);

    entries->setLayout(entriesLayout);
    entriesLayout->addWidget(entry1);
    entriesLayout->addWidget(separator);
    entriesLayout->addWidget(entry2);
    //entriesScroll->setBackgroundRole(QPalette::Dark);
    entriesScroll->setWidget(entries);
    entriesScroll->setWidgetResizable(true);
    mainLayout->addWidget(entriesScroll);
    mainLayout->addWidget(rules);
    setLayout(mainLayout);
    setWindowTitle(tr("Fuzzy"));


    /*
     *     imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setVisible(false);
    setCentralWidget(scrollArea);
    */
}

MainWindow::~MainWindow()
{

}
