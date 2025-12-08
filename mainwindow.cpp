#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsRectItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    connect(ui->grid_width, &QSpinBox::valueChanged, this, &MainWindow::updateUILimits);
    connect(ui->grid_height, &QSpinBox::valueChanged, this, &MainWindow::updateUILimits);

    connect(ui->generate_button, &QPushButton::pressed, this, &MainWindow::generateGrid);
    connect(ui->clear_button, &QPushButton::pressed, this, &MainWindow::clearGrid);

    updateUILimits();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUILimits()
{
    int width = ui->grid_width->value();
    int height = ui->grid_height->value();

    ui->start_x->setMaximum(width - 1);
    ui->finish_x->setMaximum(width - 1);

    ui->start_y->setMaximum(height - 1);
    ui->finish_y->setMaximum(height - 1);

    ui->wall_chance->setMaximum(width * height);
}

void MainWindow::generateGrid()
{
    int width = ui->grid_width->value();
    int height = ui->grid_height->value();

    int wall_chance = 0;
    if (ui->walls->isChecked()) {
        wall_chance = ui->wall_chance->value();
    }

    int max_distance = 0;
    if (!ui->same_distance->isChecked()) {
        max_distance = ui->max_distance->value();
    }

    grid.generate_graph(width, height, wall_chance, max_distance);
    drawGrid();
}

void MainWindow::clearGrid()
{
    scene->clear();
}

void MainWindow::drawGrid()
{
    clearGrid();

    if (grid.size() == 0) return;

    int cell_size = 20;

    QPen border(Qt::gray);
    border.setWidth(0);

    foreach (const Node& node, grid.get_graph()) {
        int x = node.x * cell_size;
        int y = node.y * cell_size;

        QColor color = Qt::white;

        if (node.wall) {
            color = Qt::black;
        }

        if (node.id == grid.get_start()) {
            color = Qt::green;
        }

        if (node.id == grid.get_finish()) {
            color = Qt::red;
        }

        QGraphicsRectItem *item = scene->addRect(x, y, cell_size, cell_size, border, QBrush(color));
        item->setData(0, node.id);
    }
}
