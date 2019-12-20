#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "user.h"
#include <QMainWindow>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void HideButtons();
    bool CheckPage();
    void NextPage();
    void BackPage();
    void SetUserData();
    std::string AddUserData();
    void UncheckNone(bool checked);

private slots:

    void on_pb_Continue_clicked();

    void on_pb_Done_clicked();

    void on_pb_Continue_Home_clicked();

    void on_pb_NoParticipation_clicked();

    void on_cb_1_clicked(bool checked);

    void on_cb_2_clicked(bool checked);

    void on_cb_3_clicked(bool checked);

    void on_cb_4_clicked(bool checked);

    void on_cb_5_clicked(bool checked);

    void on_cb_6_clicked(bool checked);

    void on_cb_7_clicked(bool checked);

    void on_cb_8_clicked(bool checked);

    void on_cb_9_clicked(bool checked);

    void on_cb_10_clicked(bool checked);

    void on_cb_11_clicked(bool checked);

    void on_cb_12_clicked(bool checked);

    void on_rb_None_clicked(bool checked);

    void on_pb_Back_clicked();

    void on_pb_lang_clicked();

    void on_pb_Examples_clicked();

private:
    Ui::MainWindow *ui;
    bool norsk = false;
};
#endif // MAINWINDOW_H
