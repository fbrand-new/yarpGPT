#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->askButton, SIGNAL(clicked()), this, SLOT(slotAskButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotAskButtonClicked()
{

    question = ui->ask->text();
    auto widget = new QListWidgetItem(question, ui->conversation);
    widget->setTextAlignment(Qt::AlignRight);
    widget->setSizeHint(QSize(0,widget->sizeHint().height()*2));
    // widget->setSizeHint(QSize(0, widget->sizeHint().height()));
    
    auto question_brush = QBrush(QColor(3, 252, 132));
    //question_brush.setStyle(Qt::Dense1Pattern);
    widget->setBackground(question_brush);
    
    const std::string answer = fakeAnswer(question.toUtf8().constData());
    new QListWidgetItem(answer.c_str(), ui->conversation);
}

std::string MainWindow::fakeAnswer(std::string question)
{
    return "Lorem ipsum dolor sit amet.";
}