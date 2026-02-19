#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLabel* imageLabel;
    QListWidget* listWidget;
    QPushButton* prevButton;
    QPushButton* nextButton;

    QStringList images;
    int currentIndex;
    QString imagesPath;

    const int WINDOW_WIDTH = 900;
    const int WINDOW_HEIGHT = 600;
    const int IMAGE_FIXED_SIZE = 400;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(void);

private:
    void setupUI(void);
    void displayCurrentImage(void);
    void loadImagesFromFolder(const QString& path);

private slots:
    void onPrevClicked(void);
    void onNextClicked(void);

    void onImageSelected(int row);

    void updateButtons(void);


};
#endif // MAINWINDOW_H
