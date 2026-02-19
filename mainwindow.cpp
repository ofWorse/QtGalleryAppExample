#include "mainwindow.h"

#include <QDir>
#include <QHBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , currentIndex(-1)
{
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setWindowTitle("Images galery");

    imagesPath = "<your_folder_here>";

    setupUI();

    loadImagesFromFolder(imagesPath);

    connect(prevButton, &QPushButton::clicked, this, &MainWindow::onPrevClicked);
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::onNextClicked);
    connect(listWidget, &QListWidget::currentRowChanged, this, &MainWindow::onImageSelected);

    updateButtons();
}

void MainWindow::setupUI(void)
{
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    QWidget* leftPanel = new QWidget;
    QVBoxLayout* leftLayout = new QVBoxLayout(leftPanel);

    QLabel* listLabel = new QLabel("Images:");
    listWidget = new QListWidget;
    listWidget->setMinimumWidth(200);

    leftLayout->addWidget(listLabel);
    leftLayout->addWidget(listWidget);

    QWidget* rightPanel = new QWidget;
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);

    imageLabel = new QLabel;
    imageLabel->setFixedSize(IMAGE_FIXED_SIZE, IMAGE_FIXED_SIZE);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet("border: 2px solid gray; background-color: #f0f0f0;");
    imageLabel->setText("No image");

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    prevButton = new QPushButton("← Prev");
    nextButton = new QPushButton("Next →");

    prevButton->setMinimumSize(100, 40);
    nextButton->setMinimumSize(100, 40);

    buttonLayout->addWidget(prevButton);
    buttonLayout->addWidget(nextButton);
    buttonLayout->setAlignment(Qt::AlignCenter);

    QLabel* infoLabel = new QLabel("Navigation through images");
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setStyleSheet("font-weight: bold; color: #555; margin: 10px;");

    rightLayout->addWidget(infoLabel);
    rightLayout->addWidget(imageLabel, 0, Qt::AlignCenter);
    rightLayout->addLayout(buttonLayout);
    rightLayout->addStretch();

    mainLayout->addWidget(leftPanel);
    mainLayout->addWidget(rightPanel, 1);

    mainLayout->setStretchFactor(leftPanel, 1);
    mainLayout->setStretchFactor(rightPanel, 2);
}

void MainWindow::loadImagesFromFolder(const QString &path)
{
    QDir directory(path);

    if(!directory.exists())
    {
        QMessageBox::warning(this, "Error",
                             "Folder with images not found:\n" + path);
        return;
    }

    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp" << "*.gif";

    images = directory.entryList(filters, QDir::Files);

    listWidget->clear();

    foreach(const QString &file, images)
    {
        listWidget->addItem(file);
    }

    if(!images.isEmpty())
    {
        currentIndex = 0;
        listWidget->setCurrentRow(0);
        displayCurrentImage();
    }
    else
    {
        imageLabel->setText("No images in folder");
    }
}

void MainWindow::displayCurrentImage(void)
{
    if(currentIndex >= 0 && currentIndex < images.size())
    {
        QString fullPath = imagesPath + "/" + images[currentIndex];
        QPixmap pixmap(fullPath);

        if(!pixmap.isNull())
        {
            QPixmap scaledPixmap = pixmap.scaled(IMAGE_FIXED_SIZE, IMAGE_FIXED_SIZE,
                                                  Qt::KeepAspectRatio,
                                                  Qt::SmoothTransformation);
            imageLabel->setPixmap(scaledPixmap);

            setWindowTitle(QString("Gallery - %1 (%2 of %3)")
                          .arg(images[currentIndex])
                          .arg(currentIndex + 1)
                          .arg(images.size()));
        }
        else
        {
            imageLabel->setText("Unable to load\n" + images[currentIndex]);
        }
    }

    updateButtons();
}

MainWindow::~MainWindow(void)
{
}

void MainWindow::onPrevClicked(void)
{
    if(currentIndex > 0)
    {
        currentIndex--;
        listWidget->setCurrentRow(currentIndex);
        // displayCurrentImage(); // we don't need this method, because of signals.
    }
}

void MainWindow::onNextClicked(void)
{
    if(currentIndex < images.size() - 1)
    {
        currentIndex++;
        listWidget->setCurrentRow(currentIndex);
    }
}

void MainWindow::onImageSelected(int row)
{
    if(row >= 0 && row < images.size())
    {
        currentIndex = row;
        displayCurrentImage();
    }
}

void MainWindow::updateButtons(void)
{
    prevButton->setEnabled(currentIndex > 0);
    nextButton->setEnabled(currentIndex < images.size() - 1);
}

