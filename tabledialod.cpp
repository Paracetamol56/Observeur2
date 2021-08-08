#include "tabledialog.h"
#include "ui_tabledialog.h"

///
/// Constructor
/// \brief TableDialog::TableDialog
/// \param parent
///
TableDialog::TableDialog(QWidget *parent, QSqlDatabase *database)
    : QDialog(parent)
    , m_ui(new Ui::TableDialog)
    , m_db(database)
{
    // ########################## Setup the UI ######################### //

    m_ui->setupUi(this);
}


///
/// Destructor
/// \brief TableDialog::~TableDialog
///
TableDialog::~TableDialog()
{
    delete m_ui;
}
