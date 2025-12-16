#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QListWidgetItem>

#include "grid.h"
#include "graph_types.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject* watcher, QEvent* event) override;

private:
    static const int cell_size = 20;
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    Grid grid;

    std::vector<QGraphicsRectItem*> scene_cache;
    QMap<QString, Result> solutions;
    int last_toggled_id = -1;

    void redraw_cell(int id);
    void draw_solution(QString& key);

    void setup_algorithms();
    Result run_algorithm(QString& key);

    void delay(int milliseconds);

    void update_color(QListWidgetItem *item, QColor color);
    void change_color(QListWidgetItem *item);

private slots:
    void update_limits();

    void generate_grid();
    void clear_grid();
    void draw_grid();
    void restore_grid();

    void change_endpoints();
    void generate_random_endpoints();

    void find_solution();
    void visualize_finding();
    void clear_solution();
};

#endif // MAINWINDOW_H
