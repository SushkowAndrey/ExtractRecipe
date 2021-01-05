#ifndef SELECTINGORGANIZATION_H
#define SELECTINGORGANIZATION_H

#include <QDialog>
#include "organization.h"

namespace Ui {
class SelectingOrganization;
}

class SelectingOrganization : public QDialog
{
    Q_OBJECT

public:
    explicit SelectingOrganization(QWidget *parent = nullptr);
    ~SelectingOrganization();

private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_further_clicked();

private:
    Ui::SelectingOrganization *ui;
    Organization * organization;
};

#endif // SELECTINGORGANIZATION_H
