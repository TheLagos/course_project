#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

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

    connect(ui->start_x, &QSpinBox::valueChanged, this, &MainWindow::change_endpoints);
    connect(ui->start_y, &QSpinBox::valueChanged, this, &MainWindow::change_endpoints);
    connect(ui->finish_x, &QSpinBox::valueChanged, this, &MainWindow::change_endpoints);
    connect(ui->finish_y, &QSpinBox::valueChanged, this, &MainWindow::change_endpoints);

    connect(ui->random_button, &QPushButton::pressed, this, &MainWindow::generate_random_endpoints);

    updateUILimits();

    scene->installEventFilter(this);
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
    scene_cache.clear();
}

void MainWindow::drawGrid()
{
    clearGrid();

    if (grid.size() == 0) return;

    QPen border(Qt::gray);
    border.setWidth(0);

    ui->start_x->blockSignals(true);
    ui->start_y->blockSignals(true);
    ui->finish_x->blockSignals(true);
    ui->finish_y->blockSignals(true);

    foreach (const Node& node, grid.get_graph()) {
        int x = node.x * cell_size;
        int y = node.y * cell_size;

        QColor color = Qt::white;

        if (node.wall) {
            color = Qt::black;
        }

        if (node.id == grid.get_start()) {
            color = Qt::green;
            ui->start_x->setValue(node.x);
            ui->start_y->setValue(node.y);
        }

        if (node.id == grid.get_finish()) {
            color = Qt::red;
            ui->finish_x->setValue(node.x);
            ui->finish_y->setValue(node.y);
        }

        QGraphicsRectItem* item = scene->addRect(x, y, cell_size, cell_size, border, QBrush(color));
        item->setData(0, node.id);
        scene_cache.push_back(item);

        ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    }

    ui->start_x->blockSignals(false);
    ui->start_y->blockSignals(false);
    ui->finish_x->blockSignals(false);
    ui->finish_y->blockSignals(false);
}

void MainWindow::redraw_cell(int id) {
    bool is_start = (grid.get_start() == id);
    bool is_finish = (grid.get_finish() == id);
    bool is_wall = grid.get_graph()[id].wall;

    QGraphicsRectItem* item = scene_cache[id];
    QRectF rect = item->rect();
    QBrush brush;

    if (is_start && is_finish) {
        QLinearGradient gradient(rect.topLeft(), rect.bottomRight());
        gradient.setColorAt(0.5, Qt::green);
        gradient.setColorAt(0.501, Qt::red);
        brush = QBrush(gradient);
    }
    else if (is_start) {
        brush = QBrush(Qt::green);
    }
    else if (is_finish) {
        brush = QBrush(Qt::red);
    }
    else if (is_wall) {
        brush = QBrush(Qt::black);
    }
    else {
        brush = QBrush(Qt::white);
    }

    item->setBrush(brush);
}

void MainWindow::change_endpoints() {
    if (!scene_cache.empty()) {
        int width = grid.get_width();

        int old_start_id = grid.get_start();
        int old_finish_id = grid.get_finish();

        int new_start_id = ui->start_y->value() * width + ui->start_x->value();
        int new_finish_id = ui->finish_y->value() * width + ui->finish_x->value();

        if (new_start_id == old_start_id && new_finish_id == old_finish_id) return;

            grid.set_start(new_start_id);
            grid.set_finish(new_finish_id);

            redraw_cell(old_start_id);
                        redraw_cell(old_finish_id);
            redraw_cell(new_start_id);
            redraw_cell(new_finish_id);
    }
}

void MainWindow::generate_random_endpoints() {
    if (!scene_cache.empty()) {
        int old_start_id = grid.get_start();
        int old_finish_id = grid.get_finish();

        grid.random_endpoints();
        int start_id = grid.get_start();
        int finish_id = grid.get_finish();

        redraw_cell(old_start_id);
        redraw_cell(old_finish_id);

        ui->start_x->setValue(grid.get_graph()[start_id].x);
        ui->start_y->setValue(grid.get_graph()[start_id].y);

        ui->finish_x->setValue(grid.get_graph()[finish_id].x);
        ui->finish_y->setValue(grid.get_graph()[finish_id].y);
    }
}

bool MainWindow::eventFilter(QObject* watched, QEvent* event) {
    if (watched == scene && !scene_cache.empty()) {
        if ( event->type() == QEvent::GraphicsSceneMousePress || event->type() == QEvent::GraphicsSceneMouseMove ) {
            QGraphicsSceneMouseEvent *mouse_event = static_cast<QGraphicsSceneMouseEvent*>(event);

            if (mouse_event->buttons() & Qt::LeftButton) {
                QPointF pos = mouse_event->scenePos();

                if (pos.x() < 0 || pos.y() < 0) return true;

                int x = static_cast<int>(pos.x() / cell_size);
                int y = static_cast<int>(pos.y() / cell_size);

                if (x >= grid.get_width() || y >= grid.get_height()) return true;

                int cell_id = y * grid.get_width() + x;

                if (last_toggled_id != cell_id) {
                    if (grid.get_start() != cell_id || grid.get_finish() != cell_id) {
                        grid.toggle_wall(cell_id);
                        redraw_cell(cell_id);
                        last_toggled_id = cell_id;
                    }
                }
            }
            return true;
        }

        if (event->type() == QEvent::GraphicsSceneMouseRelease) {
            last_toggled_id = -1;
        }
    }
    return QMainWindow::eventFilter(watched, event);
}
