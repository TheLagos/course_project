#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algorithms.h"

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QColorDialog>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    connect(ui->grid_width, &QSpinBox::valueChanged, this, &MainWindow::update_limits);
    connect(ui->grid_height, &QSpinBox::valueChanged, this, &MainWindow::update_limits);

    connect(ui->generate_button, &QPushButton::pressed, this, &MainWindow::generate_grid);
    connect(ui->clear_button, &QPushButton::pressed, this, &MainWindow::clear_grid);

    connect(ui->start_x, &QSpinBox::valueChanged, this, &MainWindow::change_endpoints);
    connect(ui->start_y, &QSpinBox::valueChanged, this, &MainWindow::change_endpoints);
    connect(ui->finish_x, &QSpinBox::valueChanged, this, &MainWindow::change_endpoints);
    connect(ui->finish_y, &QSpinBox::valueChanged, this, &MainWindow::change_endpoints);

    connect(ui->random_button, &QPushButton::pressed, this, &MainWindow::generate_random_endpoints);

    connect(ui->search_button, &QPushButton::pressed, this, &MainWindow::find_solution);
    connect(ui->clear_solution_button, &QPushButton::pressed, this, &MainWindow::clear_solution);

    connect(ui->solution_chooser, &QComboBox::currentIndexChanged, this, &MainWindow::visualize_finding);

    update_limits();
    setup_algorithms();

    scene->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_limits()
{
    int width = ui->grid_width->value();
    int height = ui->grid_height->value();

    ui->start_x->setMaximum(width - 1);
    ui->finish_x->setMaximum(width - 1);

    ui->start_y->setMaximum(height - 1);
    ui->finish_y->setMaximum(height - 1);
}

void MainWindow::generate_grid()
{
    clear_grid();

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
    draw_grid();
}

void MainWindow::clear_grid()
{
    scene->clear();
    scene_cache.clear();
    solutions.clear();
    ui->solution_chooser->clear();
}

void MainWindow::draw_grid()
{
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
        clear_solution();

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
        clear_solution();

        int old_start_id = grid.get_start();
        int old_finish_id = grid.get_finish();

        grid.random_endpoints();
        int start_id = grid.get_start();
        int finish_id = grid.get_finish();

        redraw_cell(old_start_id);
        redraw_cell(old_finish_id);

        ui->start_x->blockSignals(true);
        ui->start_y->blockSignals(true);
        ui->finish_x->blockSignals(true);
        ui->finish_y->blockSignals(true);

        ui->start_x->setValue(grid.get_graph()[start_id].x);
        ui->start_y->setValue(grid.get_graph()[start_id].y);
        ui->finish_x->setValue(grid.get_graph()[finish_id].x);
        ui->finish_y->setValue(grid.get_graph()[finish_id].y);

        ui->start_x->blockSignals(false);
        ui->start_y->blockSignals(false);
        ui->finish_x->blockSignals(false);
        ui->finish_y->blockSignals(false);

        redraw_cell(start_id);
        redraw_cell(finish_id);
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

void MainWindow::update_color(QListWidgetItem *item, QColor color) {
    QPixmap pixmap(16, 16);
    pixmap.fill(color);
    item->setIcon(QIcon(pixmap));
}

void MainWindow::change_color(QListWidgetItem *item) {
    QColor current = item->data(Qt::UserRole + 1).value<QColor>();
    QColor new_color = QColorDialog::getColor(current, this, "Виберіть колір алгоритму");

    if (new_color.isValid()) {
        item->setData(Qt::UserRole + 1, new_color);
        update_color(item, new_color);
    }
}

void MainWindow::setup_algorithms() {
    struct algorithm_line { QString name; QColor color; };
    QList<algorithm_line> algorithms = {
        {"BFS", Qt::green},
        {"Dijkstra", Qt::blue},
        {"AStar", Qt::cyan}
    };

    for (const auto &algorithm : algorithms) {
        QListWidgetItem *item = new QListWidgetItem(algorithm.name, ui->algorithms_list);

        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);

        item->setData(Qt::UserRole + 1, algorithm.color);
        update_color(item, algorithm.color);
    }

    connect(ui->algorithms_list, &QListWidget::itemDoubleClicked, this, &MainWindow::change_color);
}

Result MainWindow::run_algorithm(QString& key) {
    if (key == "BFS") {
        return bfs(grid);
    }
    else if (key == "Dijkstra") {
        return dijkstra(grid);
    }
    else if (key == "AStar") {
        return a_star(grid);
    }
    return Result();
}

void MainWindow::delay(int milliseconds) {
    QEventLoop loop;
    QTimer::singleShot(milliseconds, &loop, &QEventLoop::quit);
    loop.exec();
}

void MainWindow::draw_solution(QString& key) {
    const Result& result = solutions[key];
    if (result.found) {
        auto items = ui->algorithms_list->findItems(key, Qt::MatchExactly);
        if (items.empty()) return;

        QListWidgetItem* item = items.first();
        QColor color = item->data(Qt::UserRole + 1).value<QColor>();

        QGraphicsRectItem* cell;
        for (const int id : result.path) {
            if (id != grid.get_start() && id != grid.get_finish()) {
                cell = scene_cache[id];
                cell->setBrush(color);
                delay(50);
            }
        }
    }
}

void MainWindow::visualize_finding() {
    restore_grid();

    QString key = ui->solution_chooser->currentText();
    if (key.isEmpty() || solutions.find(key) == solutions.end()) return;

    const Result& result = solutions[key];
    if (result.found) {
        auto items = ui->algorithms_list->findItems(key, Qt::MatchExactly);
        if (items.empty()) return;

        QListWidgetItem* item = items.first();
        QColor color = item->data(Qt::UserRole + 1).value<QColor>();
        color.setAlpha(128);

        QGraphicsRectItem* cell;
        for (const int id : result.visited_nodes) {
            if (id != grid.get_start() && id != grid.get_finish()) {
                cell = scene_cache[id];
                cell->setBrush(color);
                delay(20);
            }
        }
        draw_solution(key);
    }
}

void MainWindow::find_solution() {
    if (scene_cache.empty()) return;

    ui->solution_chooser->blockSignals(true);
    solutions.clear();
    ui->solution_chooser->clear();
    ui->solution_chooser->blockSignals(false);

    restore_grid();

    QStringList selected_keys;
    int count = ui->algorithms_list->count();

    for (int row = 0; row < count; ++row) {
        QListWidgetItem* item = ui->algorithms_list->item(row);
        if (item->checkState()) {
            selected_keys.append(item->text());
        }
    }

    ui->solution_chooser->blockSignals(true);

    QString key;
    foreach(key, selected_keys) {
        solutions[key] = { run_algorithm(key) };
        ui->solution_chooser->addItem(key);
    }

    ui->solution_chooser->blockSignals(false);

    if (ui->solution_chooser->count() > 0) {
        ui->solution_chooser->setCurrentIndex(0);
        visualize_finding();
    }
}

void MainWindow::clear_solution() {
    ui->solution_chooser->blockSignals(true);
    solutions.clear();
    ui->solution_chooser->clear();
    ui->solution_chooser->blockSignals(false);

    restore_grid();
}

void MainWindow::restore_grid() {
    if (scene_cache.empty()) return;

    for (int i = 0; i < grid.size(); ++i) {
        if (i == grid.get_start() || i == grid.get_finish()) continue;

        const Node& node = grid.get_graph()[i];
        QGraphicsRectItem* item = scene_cache[i];

        if (node.wall) {
            item->setBrush(Qt::black);
        } else {
            item->setBrush(Qt::white);
        }
    }
}

