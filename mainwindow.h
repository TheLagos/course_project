#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "grid.h"

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

    void redraw_cell(int id);

    int last_toggled_id = -1;

private slots:
    void updateUILimits();
    void generateGrid();
    void clearGrid();
    void drawGrid();
    void change_endpoints();
    void generate_random_endpoints();
};

#endif // MAINWINDOW_H
