#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
#include <QTimer>
#include <QMessageBox>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtDebug>
#include <string>
#include <list>

user userlist;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer::singleShot(0, this, SLOT(showFullScreen()));
    ui->stackedWidget->setCurrentIndex(0);
    HideButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetUserData(){
    //Tools
    auto Tools_cb = ui->Tools->findChildren<QCheckBox*>();
    std::list<std::string> Tools;
    for(int i = 0;i<Tools_cb.size();i++){
        if(Tools_cb.at(i)->isChecked()){
            //Tools.push_back(Tools_cb.at(i)->text().toStdString());
            Tools.push_back("Yes");
            Tools_cb.at(i)->setChecked(false);
        }else{
            Tools.push_back("No");
        }
    }
    ui->rb_None->setChecked(true);
    userlist.setTools(Tools);

    //Faculty
    auto Fac_rb = ui->Hours_Fac->findChildren<QRadioButton*>();
    for(int i = 0;i<Fac_rb.size();i++){
        if(Fac_rb.at(i)->isChecked()){
            userlist.setFaculty(i);
            Fac_rb.at(i)->setAutoExclusive(false);
            Fac_rb.at(i)->setChecked(false);
            Fac_rb.at(i)->setAutoExclusive(true);
            break;
        }if(i==Fac_rb.size()-1)
            userlist.setFaculty(Fac_rb.size());
    }

    //Time Spend
    userlist.SetTimeSpend(ui->ddm_Time->currentIndex());
    ui->ddm_Time->setCurrentIndex(0);

    //Rating
    auto Rat_rb = ui->Survey->findChildren<QRadioButton*>();
    for(int i = 0;i<Rat_rb.size();i++){
        if(Rat_rb.at(i)->isChecked()){
            userlist.setSatisfaction(i);
            Rat_rb.at(i)->setAutoExclusive(false);
            Rat_rb.at(i)->setChecked(false);
            Rat_rb.at(i)->setAutoExclusive(true);
            break;
        }else if(i==Rat_rb.size()-1)
            userlist.setSatisfaction(Rat_rb.size());
    }

    //Feedback
    userlist.setFeedback(ui->TE_Feedback->toPlainText().toStdString());
    ui->TE_Feedback->setPlainText("");
}

void MainWindow::HideButtons(){
    if(ui->stackedWidget->currentIndex()==0||ui->stackedWidget->currentIndex()==1){
        ui->pb_Back->setVisible(false);
        ui->pb_Continue->setVisible(false);
    }else{
        ui->pb_Back->setVisible(true);
        ui->pb_Continue->setVisible(true);
    }
}

bool MainWindow::CheckPage(){
    if(ui->stackedWidget->currentIndex()==3){
        if(!(ui->rb_Fac1->isChecked()||ui->rb_Fac2->isChecked()||
                ui->rb_Fac3->isChecked()||ui->rb_Fac4->isChecked()||ui->rb_Fac5->isChecked())){
            if(norsk){
                QMessageBox::warning(this, "Glemte du noe?", "Vennligst velg fakultetet du tilhører");
            }else{
                QMessageBox::warning(this, "Did you forget something?", "Please select your faculty");
            }
            return false;
        }else if(ui->ddm_Time->currentIndex()==0){
            if(norsk){
                QMessageBox::warning(this, "Glemte du noe?", "Vennligst velg tiden du har brukt på Makerspace");
            }else{
                QMessageBox::warning(this, "Did you forget something?", "Please select the amount of time you have spent at the Makerspace");
            }
            return false;
        }
    }
    if(ui->stackedWidget->currentIndex()==4 &&!(ui->rb_smiley1->isChecked()||ui->rb_smiley2->isChecked()||
            ui->rb_smiley3->isChecked()||ui->rb_smiley4->isChecked())){
        if(norsk){
            QMessageBox::warning(this, "Glemte du noe?", "Klikk på et av ansiktene for å velge din tilfredshet");
        }else{
            QMessageBox::warning(this, "Did you forget something?", "Please click on one of the faces to select your satisfaction");
        }
        return false;
    }
    if(ui->stackedWidget->currentIndex()==5 && (ui->rb_smiley1->isChecked()||ui->rb_smiley2->isChecked())){
        if(ui->TE_Feedback->toPlainText().size() == 0){
            if(norsk){
                QMessageBox::warning(this, "Glemte du noe?", "Du har valgt at du ikke var fornøyd med Makerspace i dag.\nVennligst fortell oss hva vi kan gjøre, slik at du blir mer fornøyd.");
            }else{
                QMessageBox::warning(this, "Please give us feedback", "You have selected that you were unsatisfied with the Makerspace today.\nPlease tell us what we can do so you will be more satisfied.");
            }
            return false;
        }else if(ui->TE_Feedback->toPlainText().size() < 10){
            if(norsk){
                QMessageBox::warning(this, "Ikke nok", "Vennligst skriv en full setning slik at det blir enklere for oss å hjelpe deg.");
            }else{
                QMessageBox::warning(this, "Not enough", "Please write down a full sentence, this will make it easier for us to help you.");
            }
            return false;
        }
    }
    return true;
}

void MainWindow::NextPage(){
    if(CheckPage()){
        if(ui->stackedWidget->currentIndex()==5){
            SetUserData();
            userlist.userAdd(false);
            ui->stackedWidget->setCurrentIndex(0);
        }else {
            int go = ui->stackedWidget->currentIndex()+1;
            ui->stackedWidget->setCurrentIndex(go);
        }
        HideButtons();
    }
}

void MainWindow::BackPage(){
    int back = ui->stackedWidget->currentIndex()-1;
    ui->stackedWidget->setCurrentIndex(back);
    HideButtons();
}

void MainWindow::on_pb_lang_clicked()
{
    if(norsk){
        ui->pb_Done->setText("Done for today?");
        ui->pb_Continue->setText("Continue");
        ui->l_Survey_Explain->setText("We want to know more about how the Makerspace is used. So please answer the next four questions. This information cannot be tracked back to you.");
        ui->pb_Continue_Home->setText("Continue");
        ui->pb_NoParticipation->setText("Rather not");
        ui->l_Tools_h1->setText("What tools have you used today?");
        ui->l_Tools_Explain->setText("Please check all the boxes that apply");
        ui->cb_1->setText("3D printer");
        ui->cb_2->setText("3D scanner");
        ui->cb_3->setText("Photo table");
        ui->cb_4->setText("Vinyl cutter");
        ui->cb_5->setText("Sewing machine");
        ui->cb_6->setText("Transfer printer");
        ui->cb_7->setText("Woodworking hand tools");
        ui->cb_8->setText("Woodworking machines");
        ui->cb_9->setText("CNC machine");
        ui->cb_10->setText("Heat press");
        ui->cb_11->setText("Soldering iron");
        ui->cb_12->setText("Laser cutter");
        ui->rb_None->setText("None");
        ui->l_Faculty_h1->setText("What faculty are you in?");
        ui->rb_Fac5->setText("None");
        ui->l_Time_h1->setText("How many hours have you spent at Makerspace today?");
        //List of times
        ui->ddm_Time->setItemText(0,"");
        ui->ddm_Time->setItemText(1,"0.5 hour");
        ui->ddm_Time->setItemText(2,"1 hour");
        ui->ddm_Time->setItemText(3,"1.5 hours");
        ui->ddm_Time->setItemText(4,"2 hours");
        ui->ddm_Time->setItemText(5,"2.5 hours");
        ui->ddm_Time->setItemText(6,"3 hours");
        ui->ddm_Time->setItemText(7,"3.5 hours");
        ui->ddm_Time->setItemText(8,"4 hours");
        ui->ddm_Time->setItemText(9,"4.5 hours");
        ui->ddm_Time->setItemText(10,"5 hours");
        ui->ddm_Time->setItemText(11,"5.5 hours");
        ui->ddm_Time->setItemText(12,"6 hours");
        ui->l_Happy_h1->setText("How happy are you with the Makerspace today?");
        ui->pb_Examples->setText("Examples");
        ui->pb_lang->setStyleSheet("border-image: url(:/img/img/no.png) 0 0 0 0 stretch stretch;\n");
        norsk = false;
    }else{
        ui->pb_Done->setText("Ferdig for i dag?");
        ui->pb_Continue->setText("Gå videre");
        ui->l_Survey_Explain->setText("vi vil vite mer om hvordan Makerspace blir brukt. Så vennligst svar på de neste fire spørsmålene. Denne informasjonen kan ikke spores tilbake til deg.");
        ui->pb_Continue_Home->setText("Gå videre");
        ui->pb_NoParticipation->setText("Nei takk!");
        ui->l_Tools_h1->setText("Hvilke utstyr har du brukt i dag?");
        ui->l_Tools_Explain->setText("Velg utstyr nedenfor");
		ui->cb_1->setText("3D printer");
        ui->cb_2->setText("3D skanner");
        ui->cb_3->setText("Fotobord");
        ui->cb_4->setText("Vinylkutter");
        ui->cb_5->setText("Symaskin");
        ui->cb_6->setText("Transfer printer");
        ui->cb_7->setText("Treverksted: Håndverktøy");
        ui->cb_8->setText("Treverksted: Maskiner");
        ui->cb_9->setText("CNC maskin");
        ui->cb_10->setText("Varmepresser");
        ui->cb_11->setText("Loddebolt");
        ui->cb_12->setText("Laserkutter");
		ui->rb_None->setText("Ingenting");
        ui->l_Faculty_h1->setText("Hvilket fakultet tilhører du?");
        ui->rb_Fac5->setText("ingen");
        ui->l_Time_h1->setText("Hvor lang tid har du brukt i Makerspace idag?");
        //List of times
        ui->ddm_Time->setItemText(0,"");
        ui->ddm_Time->setItemText(1,"0.5 time");
        ui->ddm_Time->setItemText(2,"1 time");
        ui->ddm_Time->setItemText(3,"1.5 timer");
        ui->ddm_Time->setItemText(4,"2 timer");
        ui->ddm_Time->setItemText(5,"2.5 timer");
        ui->ddm_Time->setItemText(6,"3 timer");
        ui->ddm_Time->setItemText(7,"3.5 timer");
        ui->ddm_Time->setItemText(8,"4 timer");
        ui->ddm_Time->setItemText(9,"4.5 timer");
        ui->ddm_Time->setItemText(10,"5 timer");
        ui->ddm_Time->setItemText(11,"5.5 timer");
        ui->ddm_Time->setItemText(12,"6 timer");
        ui->l_Happy_h1->setText("Hvor fornøyd er du med Makerspace i dag?");
        ui->pb_Examples->setText("Eksempler");
        ui->pb_lang->setStyleSheet("border-image: url(:/img/img/en.png) 0 0 0 0 stretch stretch;\n");
        norsk = true;
    }
}
void MainWindow::on_pb_Back_clicked()
{
    BackPage();
}

void MainWindow::on_pb_Continue_clicked()
{
    NextPage();
}

void MainWindow::on_pb_Done_clicked()
{
    NextPage();
}

void MainWindow::on_pb_Continue_Home_clicked()
{
    NextPage();
}

void MainWindow::on_pb_NoParticipation_clicked()
{
    SetUserData();
    userlist.userAdd(true);
    BackPage();
}

void MainWindow::UncheckNone(bool checked){
    if(checked){
        ui->rb_None->setChecked(false);
    }
}

void MainWindow::on_cb_1_clicked(bool checked)
{
    UncheckNone(checked);
}

void MainWindow::on_cb_2_clicked(bool checked)
{
    UncheckNone(checked);
}

void MainWindow::on_cb_3_clicked(bool checked)
{
    UncheckNone(checked);
}

void MainWindow::on_cb_4_clicked(bool checked)
{
    UncheckNone(checked);
}

void MainWindow::on_cb_5_clicked(bool checked)
{
    UncheckNone(checked);
}

void MainWindow::on_cb_6_clicked(bool checked)
{
    UncheckNone(checked);
}

void MainWindow::on_cb_7_clicked(bool checked)
{
    UncheckNone(checked);
}

void MainWindow::on_cb_8_clicked(bool checked)
{
    UncheckNone(checked);
}

void MainWindow::on_cb_9_clicked(bool checked)
{
    UncheckNone(checked);
}

void MainWindow::on_cb_10_clicked(bool checked)
{
    UncheckNone(checked);
}

void MainWindow::on_cb_11_clicked(bool checked)
{
    UncheckNone(checked);
}

void MainWindow::on_cb_12_clicked(bool checked)
{
    UncheckNone(checked);
}


void MainWindow::on_rb_None_clicked(bool checked)
{
    if(checked){
        ui->cb_1->setChecked(false);
        ui->cb_2->setChecked(false);
        ui->cb_3->setChecked(false);
        ui->cb_4->setChecked(false);
        ui->cb_5->setChecked(false);
        ui->cb_6->setChecked(false);
        ui->cb_7->setChecked(false);
        ui->cb_8->setChecked(false);
        ui->cb_9->setChecked(false);
        ui->cb_10->setChecked(false);
        ui->cb_11->setChecked(false);
        ui->cb_12->setChecked(false);
    }
}

void MainWindow::on_pb_Examples_clicked()
{
    if(norsk){
        QMessageBox::information(this, "Eksempler", "Det var kaldt inne\nIngen som hjalp meg\nJeg ble skadet\nJeg har lært masse!\nJeg fikk mye hjelp.");
    }else{
        QMessageBox::information(this, "Examples", "I didn't get any help\nThe tool didn't work\nI got stabbed\nI learned a lot\nI got some good help.");
    }
}
