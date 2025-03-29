#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QFont>
#include <QStackedWidget>
#include <QGraphicsDropShadowEffect>
#include <QTimer>
#include <QPalette>
#include <QIcon>
#include <QPixmap>
#include<iostream>
#include<ostream>


using namespace std;

template<class T>
class ChainNode {
public:
    T data; // �������� ������� �� ������
    ChainNode<T>* link; // ���� ��� ������ �������
};

template<class T>
class Chain {
public:
    Chain() { first = nullptr; } // ������� ���� ������� �����
    ~Chain(); // ������� ������ �������
    bool IsEmpty() const { return first == nullptr; } // ������ ��� ���� ������� �����
    int Length() const; // ����� ��� �������
    bool Find(int k, T& x) const; // ����� �� ������ �� ������ k
    int Search(const T& x) const; // ����� �� ���� ������ ������ �����
    void Insert(int k, const T& x); // ����� ���� �� ������ k
    void Delete(int k, T& x); // ��� ���� �� ������ k ������ �����
    void Output(ostream& out) const; // ����� ����� �������
    T Max_Second() const; // ����� ���� ���� ���� �� �������
    void Clear(); // ��� ���� ����� �� �������

private:
    ChainNode<T>* first; // ���� ��� ������ ������ �� �������
};

// ������� ���� ���� �����
template<class T>
Chain<T>::~Chain() {
    Clear(); // ��� ���� ����� ��� ����� �������
}

template<class T>
int Chain<T>::Length() const { // ���� ��� �������
    ChainNode<T>* current = first; // ����� �� ������ ������
    int len = 0; // ��� ������� ���� �� �����
    while (current) { // ������ �����
        len++; // ����� �����
        current = current->link; // �������� ��� ������ �������
    }
    return len; // ����� ����� �������
}

template<class T>
bool Chain<T>::Find(int k, T& x) const { // ����� �� ������ �� ������ k
    if (k < 1) return false; // ������ �� ������ ������
    ChainNode<T>* current = first; // ����� �� ������ ������
    int index = 1; // ������� ���� �� 1

    while (index < k && current) { // ����� ��� ������ ��������
        current = current->link; // �������� ��� ������ �������
        index++; // ����� ������
    }

    if (current) { // ��� ����� ������
        x = current->data; // ����� ��������
        return true; // �� ������ ��� ������
    }
    return false; // ������ ��� �����
}

template<class T>
void Chain<T>::Insert(int k, const T& x) { // ����� ���� �� ������ k
    ChainNode<T>* newNode = new ChainNode<T>; // ����� ���� �����
    newNode->data = x; // ����� �������� �� ������
    newNode->link = nullptr; // ����� ������ ��� nullptr

    if (k == 1 || !first) { // ������� �� ����� �������
        newNode->link = first; // ��� ������ ������� �������
        first = newNode; // ����� ������ ������
    }
    else { // ������� �� ����� ����
        ChainNode<T>* current = first; // ����� �� ������ ������
        for (int i = 1; i < k - 1 && current; ++i) { // ������ ��� ������ ������� ������ k
            current = current->link; // �������� ��� ������ �������
        }
        if (current) { // ��� ���� ������ ������� ������
            newNode->link = current->link; // ��� ������ ������� ������� k
            current->link = newNode; // ��� ������ ������� ��������
        }
        else { // ��� ��� ������ ��� ����
            delete newNode; // ��� ������ �������
            throw out_of_range("Invalid position"); // ����� �������
        }
    }
}

template<class T>
void Chain<T>::Delete(int k, T& x) { // ��� ������ �� ������ k
    if (k < 1 || !first) // ������ �� ��� ������ �� ��� ���� ������� �����
        throw out_of_range("Out of bounds"); // ����� �������

    ChainNode<T>* p = first; // ������ ��� ������ ������ �����

    if (k == 1) // ��� ��� ����� �� �������
        first = first->link; // ����� ������ ������
    else {
        ChainNode<T>* q = first; // ������ ��������
        for (int index = 1; index < k - 1 && q; index++) // ������ ��� ������ ������� ������ k
            q = q->link; // �������� ��� ������ �������
        if (!q || !q->link) // ������ �� ��� ������
            throw out_of_range("Out of bounds"); // ����� �������
        p = q->link; // ������� ��� ������ ������ �����
        q->link = p->link; // ����� ������ ��������
    }

    x = p->data; // ��� ������ ������ ��������
    delete p; // ��� ������
}

template<class T>
int Chain<T>::Search(const T& x) const { // ����� �� ���� ������
    ChainNode<T>* current = first; // ����� �� ������ ������
    int index = 1; // ������� ���� �� 1
    while (current) { // ������ �����
        if (current->data == x) return index; // ��� ����� �����ɡ ����� ������
        current = current->link; // �������� ��� ������ �������
        ++index; // ����� ������
    }
    return 0; // ������ ��� �����
}

template<class T>
T Chain<T>::Max_Second() const { // ����� ���� ���� ����
    if (!first || !first->link) // ������ �� ���� ������ ��� �����
        throw runtime_error("The chain must have at least two elements."); // ����� �������

    T max1 = first->data; // ���� ���� ������
    T max2 = numeric_limits<T>::lowest(); // ���� ���� ���� ������

    ChainNode<T>* current = first->link; // ����� �� ������ �������
    while (current) { // ������ �����
        if (current->data > max1) { // ����� max1 � max2
            max2 = max1; // ����� ������� ���� ���� ���� ����
            max1 = current->data; // ����� ���� ����
        }
        else if (current->data > max2 && current->data != max1) { // ����� max2
            max2 = current->data; // ����� ���� ���� ����
        }
        current = current->link; // �������� ��� ������ �������
    }

    if (max2 == numeric_limits<T>::lowest()) // ������ �� ���� ���� ���� ����
        throw runtime_error("No second maximum found."); // ����� �������
    return max2; // ����� ���� ���� ����
}

template<class T>
ostream& operator<<(ostream& out, const Chain<T>& x) { // ����� ����� ���� �������
    x.Output(out); // ����� ����� �������
    return out; // ����� ��� �������
}

template<class T>
void Chain<T>::Clear() { // ��� ���� �����
    while (first) { // ������ ������� ���� �����
        ChainNode<T>* temp = first; // ��� ������ �������
        first = first->link; // �������� ��� ������ �������
        delete temp; // ��� ������ �������
    }
}



int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QWidget window;

    window.setWindowTitle("Linked List ");

    window.setStyleSheet("background-color: #f0f0f0;");

    QVBoxLayout* layout = new QVBoxLayout;
    QLabel* titleLabel = new QLabel("Linked List ");
    QFont titleFont("Arial", 18, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("background-color: #2E8B57; color: white; padding: 10px; border-radius: 10px;");
    layout->addWidget(titleLabel);

    QLineEdit* inputField = new QLineEdit();
    inputField->setPlaceholderText("Enter a number...");
    inputField->setAlignment(Qt::AlignCenter);
    inputField->setStyleSheet("padding: 10px; font-size: 16px; border-radius: 15px; background-color: #ffffff;");
    QGraphicsDropShadowEffect* inputShadow = new QGraphicsDropShadowEffect;
    inputShadow->setBlurRadius(15);
    inputShadow->setOffset(5, 5);
    inputField->setGraphicsEffect(inputShadow);
    layout->addWidget(inputField);

    QLineEdit* positionField = new QLineEdit();
    positionField->setPlaceholderText("Enter position (optional)...");
    positionField->setAlignment(Qt::AlignCenter);
    positionField->setStyleSheet("padding: 10px; font-size: 16px; border-radius: 15px; background-color: #ffffff;");
    layout->addWidget(positionField);

    QPushButton* addButton = new QPushButton("Add Number");
    QPushButton* deleteButton = new QPushButton("Delete Number");
    QPushButton* searchButton = new QPushButton("Search Number");
    QPushButton* maxButton = new QPushButton("Find Second Maximum");
    QPushButton* clearButton = new QPushButton("Clear All");
    QPushButton* findButton = new QPushButton("Find Position");
    QPushButton* lengthButton = new QPushButton("List Length");
    QPushButton* trashButton = new QPushButton("Show Trash");
    QWidget* buttonPanel = new QWidget;
    QHBoxLayout* buttonLayout = new QHBoxLayout;


    addButton->setStyleSheet("background-color: #4CAF50; color: white; font-size: 16px; padding: 10px; border-radius: 15px;");
    deleteButton->setStyleSheet("background-color: #FF6347; color: white; font-size: 16px; padding: 10px; border-radius: 15px;");
    searchButton->setStyleSheet("background-color: #FFA500; color: white; font-size: 16px; padding: 10px; border-radius: 15px;");
    maxButton->setStyleSheet("background-color: #1E90FF; color: white; font-size: 16px; padding: 10px; border-radius: 15px;");
    clearButton->setStyleSheet("background-color: #DC143C; color: white; font-size: 16px; padding: 10px; border-radius: 15px;");
    findButton->setStyleSheet("background-color: #8A2BE2; color: white; font-size: 16px; padding: 10px; border-radius: 15px;");
    lengthButton->setStyleSheet("background-color: #4682B4; color: white; font-size: 16px; padding: 10px; border-radius: 15px;");
    trashButton->setStyleSheet("background-color: #FF8C00; color: white; font-size: 16px; padding: 10px; border-radius: 15px;");

    buttonLayout->addWidget(addButton); // ����� �� "Add Number" ��� ������� ������ ������� (buttonLayout)
    buttonLayout->addWidget(deleteButton); // ����� �� "Delete Number" ��� ������� ������ ������� (buttonLayout)
    buttonLayout->addWidget(searchButton); // ����� �� "Search Number" ��� ������� ������ ������� (buttonLayout)
    buttonLayout->addWidget(maxButton); // ����� �� "Find Second Maximum" ��� ������� ������ ������� (buttonLayout)
    buttonLayout->addWidget(findButton); // ����� �� "Find Position" ��� ������� ������ ������� (buttonLayout)
    buttonLayout->addWidget(lengthButton); // ����� �� "List Length" ��� ������� ������ ������� (buttonLayout)
    buttonLayout->addWidget(clearButton); // ����� �� "Clear All" ��� ������� ������ ������� (buttonLayout)
    buttonLayout->addWidget(trashButton); // ����� �� "Show Trash" ��� ������� ������ ������� (buttonLayout)

    buttonPanel->setLayout(buttonLayout); // �� ����� ������� ���� ����� ��� ������� ��� ��� buttonPanel

    layout->addWidget(buttonPanel);

    QListWidget* listWidget = new QListWidget();
    listWidget->setStyleSheet("background-color: #ffffff; font-size: 16px; padding: 10px; border-radius: 15px;");

    layout->addWidget(listWidget);

    QLabel* resultLabel = new QLabel("Result will appear here");
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setFont(QFont("Arial", 14));
    resultLabel->setStyleSheet("color: #2E8B57; margin-top: 20px;");

    layout->addWidget(resultLabel);

    QListWidget* trashListWidget = new QListWidget();
    trashListWidget->setStyleSheet("background-color: #ffffff; font-size: 16px; padding: 10px; border-radius: 15px;");

    trashListWidget->hide();
    layout->addWidget(trashListWidget);

    Chain<int> chain;
    int lastDeleted = 0;
    QList<int> deletedNumbers;


    // ��� ����� ��� �� �������
    QObject::connect(addButton, &QPushButton::clicked, [&]() {
        bool ok;
        int number = inputField->text().toInt(&ok);  // ����� ���� ������ ��� ��� ����
        int position = positionField->text().isEmpty() ? listWidget->count() + 1 : positionField->text().toInt(&ok); // ����� ���� �������
        if (ok) {
            try {
                chain.Insert(position, number);  // ����� ����� �� �������
                listWidget->insertItem(position - 1, QString::number(number)); // ����� ����� ��� ����� ������� �� ������ ������
                inputField->clear();            // ��� ��� �������
                positionField->clear();         // ��� ��� ������
            }
            catch (const out_of_range& e) {
                QMessageBox::warning(&window, "Insert Error", e.what());  // ����� ����� ��� ��� ���� �������
            }
        }
        else {
            QMessageBox::warning(&window, "Input Error", "Please enter valid data."); // ����� ����� ��� ��� ������� ��� ����
        }
        });

    // ��� ����� ��� �� �����
    QObject::connect(deleteButton, &QPushButton::clicked, [&]() {
        QListWidgetItem* selectedItem = listWidget->currentItem();  // ������ ��� ������ ������ ������ �� �������
        if (selectedItem) {
            int index = listWidget->row(selectedItem) + 1;  // ������ ��� ���� ������ ������
            try {
                chain.Delete(index, lastDeleted);           // ��� ������ �� �������
                delete listWidget->takeItem(index - 1);     // ����� ������ �� ����� �������
                deletedNumbers.append(lastDeleted);        // ����� ����� ������� ��� ����� ������� ��������
            }
            catch (const out_of_range& e) {
                QMessageBox::warning(&window, "Delete Error", e.what());  // ����� ����� ��� ��� ��� �����
            }
        }
        else {
            QMessageBox::warning(&window, "Selection Error", "Please select a number to delete."); // ����� ����� ��� �� ��� ����� ����
        }
        });

    // ��� ����� ��� �� ��� ������� ��������
    QObject::connect(trashButton, &QPushButton::clicked, [&]() {
        trashListWidget->clear();                          // ��� ������� ����� ��� ���������
        for (int num : deletedNumbers) {
            trashListWidget->addItem(QString::number(num)); // ����� ���� ������� �������� ��� ����� ��� ���������
        }
        trashListWidget->show();                           // ��� ����� ��� ���������
        });

    // ��� ����� ��� �� �����
    QObject::connect(searchButton, &QPushButton::clicked, [&]() {
        bool ok;
        int number = inputField->text().toInt(&ok);        // ����� ���� ������ ��� ��� ����
        if (ok) {
            int position = chain.Search(number);           // ����� �� ����� �� �������
            if (position > 0) {
                resultLabel->setText("Number found at position: " + QString::number(position)); // ��� ������ ��� �� ������ ��� �����
            }
            else {
                resultLabel->setText("Number not found."); // ������� ��� �� ����� ��� �����
            }
        }
        else {
            QMessageBox::warning(&window, "Input Error", "Please enter a valid number to search."); // ����� ����� ��� ��� ������� ��� ����
        }
        });

    // ��� ����� ��� �� ����� ���� ���� ����
    QObject::connect(maxButton, &QPushButton::clicked, [&]() {
        try {
            int secondMax = chain.Max_Second();            // ������ ��� ���� ���� ���� �� �������
            resultLabel->setText("Second maximum: " + QString::number(secondMax)); // ��� ���� ���� ����
        }
        catch (const runtime_error& e) {
            resultLabel->setText("Error: " + QString(e.what())); // ����� ����� ��� ��� ��� �������
        }
        });

    // ��� ����� ��� �� ��� �������
    QObject::connect(clearButton, &QPushButton::clicked, [&]() {
        chain.Clear();                                     // ��� ������� �������
        listWidget->clear();                               // ��� ������� ����� �������
        trashListWidget->hide();                           // ����� ����� ��� ���������
        resultLabel->setText("All items cleared.");        // ������� ��� ��� �� ��� ���� �������
        });

    // ��� ����� ��� �� ����� ���� �� ���� ����
    QObject::connect(findButton, &QPushButton::clicked, [&]() {
        bool ok;
        int position = positionField->text().toInt(&ok);   // ����� ������� �� ��� ������ ��� ��� ����
        if (ok) {
            int value;
            if (chain.Find(position, value)) {             // ����� �� ������ �� ������ ������
                resultLabel->setText("Value at position " + QString::number(position) + ": " + QString::number(value)); // ��� ������
            }
            else {
                resultLabel->setText("No value found at position " + QString::number(position)); // ������� ��� ��� �� ��� ������ ��� ����
            }
        }
        else {
            QMessageBox::warning(&window, "Input Error", "Please enter a valid position."); // ����� ����� ��� ��� ������� ��� ����
        }
        });

    // ��� ����� ��� �� ��� ��� �������
    QObject::connect(lengthButton, &QPushButton::clicked, [&]() {
        resultLabel->setText("List length: " + QString::number(chain.Length())); // ��� ��� �������
        });

    window.setLayout(layout);                               // ��� ������� ������� ��������
    window.show();                                          // ��� ������� ��������

    return app.exec();                                      // ����� �������

}
