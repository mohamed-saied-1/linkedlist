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
    T data; // ÇáÈíÇäÇÊ ÇáãÎÒäÉ İí ÇáÚŞÏÉ
    ChainNode<T>* link; // ãÄÔÑ Åáì ÇáÚŞÏÉ ÇáÊÇáíÉ
};

template<class T>
class Chain {
public:
    Chain() { first = nullptr; } // ÇáãõäÔÆ íÌÚá ÇáÓáÓáÉ İÇÑÛÉ
    ~Chain(); // ÇáãõÏãÑ áÊäÙíİ ÇáÓáÓáÉ
    bool IsEmpty() const { return first == nullptr; } // ÇáÊÍŞŞ ÅĞÇ ßÇäÊ ÇáÓáÓáÉ İÇÑÛÉ
    int Length() const; // ÅÑÌÇÚ Øæá ÇáÓáÓáÉ
    bool Find(int k, T& x) const; // ÇáÈÍË Úä ÇáÚäÕÑ İí ÇáãæŞÚ k
    int Search(const T& x) const; // ÇáÈÍË Úä ŞíãÉ ÇáÚäÕÑ æÅÑÌÇÚ ãæŞÚå
    void Insert(int k, const T& x); // ÅÏÎÇá ÚäÕÑ İí ÇáãæŞÚ k
    void Delete(int k, T& x); // ÍĞİ ÚäÕÑ ãä ÇáãæŞÚ k æÅÑÌÇÚ ŞíãÊå
    void Output(ostream& out) const; // ÅÎÑÇÌ ÚäÇÕÑ ÇáÓáÓáÉ
    T Max_Second() const; // ÅíÌÇÏ ËÇäí ÃßÈÑ ŞíãÉ İí ÇáÓáÓáÉ
    void Clear(); // ÍĞİ ÌãíÚ ÇáÚŞÏ İí ÇáÓáÓáÉ

private:
    ChainNode<T>* first; // ãÄÔÑ Åáì ÇáÚŞÏÉ ÇáÃæáì İí ÇáÓáÓáÉ
};

// ÇáãõÏãÑ áÍĞİ ÌãíÚ ÇáÚŞÏ
template<class T>
Chain<T>::~Chain() {
    Clear(); // ÍĞİ ÌãíÚ ÇáÚŞÏ ÚäÏ ÊÏãíÑ ÇáÓáÓáÉ
}

template<class T>
int Chain<T>::Length() const { // ÍÓÇÈ Øæá ÇáÓáÓáÉ
    ChainNode<T>* current = first; // ÇáÈÏÁ ãä ÇáÚŞÏÉ ÇáÃæáì
    int len = 0; // Øæá ÇáÓáÓáÉ íÈÏÃ ãä ÇáÕİÑ
    while (current) { // ÇÌÊíÇÒ ÇáÚŞÏ
        len++; // ÒíÇÏÉ ÇáØæá
        current = current->link; // ÇáÇäÊŞÇá Åáì ÇáÚŞÏÉ ÇáÊÇáíÉ
    }
    return len; // ÅÑÌÇÚ ÇáØæá ÇáäåÇÆí
}

template<class T>
bool Chain<T>::Find(int k, T& x) const { // ÇáÈÍË Úä ÇáÚäÕÑ İí ÇáãæŞÚ k
    if (k < 1) return false; // ÇáÊÍŞŞ ãä ÕáÇÍíÉ ÇáãæŞÚ
    ChainNode<T>* current = first; // ÇáÈÏÁ ãä ÇáÚŞÏÉ ÇáÃæáì
    int index = 1; // ÇáİåÑÓÉ ÊÈÏÃ ãä 1

    while (index < k && current) { // ÇáÈÍË ÍÊì ÇáÚŞÏÉ ÇáãØáæÈÉ
        current = current->link; // ÇáÇäÊŞÇá Åáì ÇáÚŞÏÉ ÇáÊÇáíÉ
        index++; // ÒíÇÏÉ ÇáİåÑÓ
    }

    if (current) { // ÅĞÇ æõÌÏÊ ÇáÚŞÏÉ
        x = current->data; // ÅÑÌÇÚ ÇáÈíÇäÇÊ
        return true; // Êã ÇáÚËæÑ Úáì ÇáÚäÕÑ
    }
    return false; // ÇáÚäÕÑ ÛíÑ ãæÌæÏ
}

template<class T>
void Chain<T>::Insert(int k, const T& x) { // ÅÏÎÇá ÚäÕÑ İí ÇáãæŞÚ k
    ChainNode<T>* newNode = new ChainNode<T>; // ÅäÔÇÁ ÚŞÏÉ ÌÏíÏÉ
    newNode->data = x; // ÊÎÒíä ÇáÈíÇäÇÊ İí ÇáÚŞÏÉ
    newNode->link = nullptr; // ÅÚÏÇÏ ÇáÑÇÈØ Åáì nullptr

    if (k == 1 || !first) { // ÇáÅÏÎÇá İí ÈÏÇíÉ ÇáÓáÓáÉ
        newNode->link = first; // ÑÈØ ÇáÚŞÏÉ ÇáÌÏíÏÉ ÈÇáÃæáì
        first = newNode; // ÊÍÏíË ÇáÚŞÏÉ ÇáÃæáì
    }
    else { // ÇáÅÏÎÇá İí ãæÇŞÚ ÃÎÑì
        ChainNode<T>* current = first; // ÇáÈÏÁ ãä ÇáÚŞÏÉ ÇáÃæáì
        for (int i = 1; i < k - 1 && current; ++i) { // ÇáæÕæá Åáì ÇáÚŞÏÉ ÇáÓÇÈŞÉ ááãæŞÚ k
            current = current->link; // ÇáÇäÊŞÇá Åáì ÇáÚŞÏÉ ÇáÊÇáíÉ
        }
        if (current) { // ÅĞÇ ßÇäÊ ÇáÚŞÏÉ ÇáÓÇÈŞÉ ãæÌæÏÉ
            newNode->link = current->link; // ÑÈØ ÇáÚŞÏÉ ÇáÌÏíÏÉ ÈÇáãæŞÚ k
            current->link = newNode; // ÑÈØ ÇáÚŞÏÉ ÇáÓÇÈŞÉ ÈÇáÌÏíÏÉ
        }
        else { // ÅĞÇ ßÇä ÇáãæŞÚ ÛíÑ ÕÍíÍ
            delete newNode; // ÍĞİ ÇáÚŞÏÉ ÇáÌÏíÏÉ
            throw out_of_range("Invalid position"); // ÅØáÇŞ ÇÓÊËäÇÁ
        }
    }
}

template<class T>
void Chain<T>::Delete(int k, T& x) { // ÍĞİ ÇáÚäÕÑ İí ÇáãæŞÚ k
    if (k < 1 || !first) // ÇáÊÍŞŞ ãä ÕÍÉ ÇáãæŞÚ Ãæ ÅĞÇ ßÇäÊ ÇáÓáÓáÉ İÇÑÛÉ
        throw out_of_range("Out of bounds"); // ÅØáÇŞ ÇÓÊËäÇÁ

    ChainNode<T>* p = first; // ÇáãÄÔÑ Åáì ÇáÚŞÏÉ ÇáãÑÇÏ ÍĞİåÇ

    if (k == 1) // ÅĞÇ ßÇä ÇáÍĞİ İí ÇáÈÏÇíÉ
        first = first->link; // ÊÍÏíË ÇáÚŞÏÉ ÇáÃæáì
    else {
        ChainNode<T>* q = first; // ÇáãÄÔÑ ááÇÌÊíÇÒ
        for (int index = 1; index < k - 1 && q; index++) // ÇáæÕæá Åáì ÇáÚŞÏÉ ÇáÓÇÈŞÉ ááãæŞÚ k
            q = q->link; // ÇáÇäÊŞÇá Åáì ÇáÚŞÏÉ ÇáÊÇáíÉ
        if (!q || !q->link) // ÇáÊÍŞŞ ãä ÕÍÉ ÇáãæŞÚ
            throw out_of_range("Out of bounds"); // ÅØáÇŞ ÇÓÊËäÇÁ
        p = q->link; // ÇáÅÔÇÑÉ Åáì ÇáÚŞÏÉ ÇáãÑÇÏ ÍĞİåÇ
        q->link = p->link; // ÊÌÇæÒ ÇáÚŞÏÉ ÇáãÍĞæİÉ
    }

    x = p->data; // ÍİÙ ÈíÇäÇÊ ÇáÚŞÏÉ ÇáãÍĞæİÉ
    delete p; // ÍĞİ ÇáÚŞÏÉ
}

template<class T>
int Chain<T>::Search(const T& x) const { // ÇáÈÍË Úä ŞíãÉ ÇáÚäÕÑ
    ChainNode<T>* current = first; // ÇáÈÏÁ ãä ÇáÚŞÏÉ ÇáÃæáì
    int index = 1; // ÇáİåÑÓÉ ÊÈÏÃ ãä 1
    while (current) { // ÇÌÊíÇÒ ÇáÚŞÏ
        if (current->data == x) return index; // ÅĞÇ æõÌÏÊ ÇáŞíãÉ¡ ÅÑÌÇÚ ÇáãæŞÚ
        current = current->link; // ÇáÇäÊŞÇá Åáì ÇáÚŞÏÉ ÇáÊÇáíÉ
        ++index; // ÒíÇÏÉ ÇáİåÑÓ
    }
    return 0; // ÇáÚäÕÑ ÛíÑ ãæÌæÏ
}

template<class T>
T Chain<T>::Max_Second() const { // ÅíÌÇÏ ËÇäí ÃßÈÑ ŞíãÉ
    if (!first || !first->link) // ÇáÊÍŞŞ ãä æÌæÏ ÚŞÏÊíä Úáì ÇáÃŞá
        throw runtime_error("The chain must have at least two elements."); // ÅØáÇŞ ÇÓÊËäÇÁ

    T max1 = first->data; // ÃßÈÑ ŞíãÉ ãÈÏÆíÉ
    T max2 = numeric_limits<T>::lowest(); // ËÇäí ÃßÈÑ ŞíãÉ ãÈÏÆíÉ

    ChainNode<T>* current = first->link; // ÇáÈÏÁ ãä ÇáÚŞÏÉ ÇáËÇäíÉ
    while (current) { // ÇÌÊíÇÒ ÇáÚŞÏ
        if (current->data > max1) { // ÊÍÏíË max1 æ max2
            max2 = max1; // ÇáŞíã ÇáÓÇÈŞÉ ÊÕÈÍ ËÇäí ÃßÈÑ ŞíãÉ
            max1 = current->data; // ÊÍÏíË ÃßÈÑ ŞíãÉ
        }
        else if (current->data > max2 && current->data != max1) { // ÊÍÏíË max2
            max2 = current->data; // ÊÍÏíË ËÇäí ÃßÈÑ ŞíãÉ
        }
        current = current->link; // ÇáÇäÊŞÇá Åáì ÇáÚŞÏÉ ÇáÊÇáíÉ
    }

    if (max2 == numeric_limits<T>::lowest()) // ÇáÊÍŞŞ ãä æÌæÏ ËÇäí ÃßÈÑ ŞíãÉ
        throw runtime_error("No second maximum found."); // ÅØáÇŞ ÇÓÊËäÇÁ
    return max2; // ÅÑÌÇÚ ËÇäí ÃßÈÑ ŞíãÉ
}

template<class T>
ostream& operator<<(ostream& out, const Chain<T>& x) { // ÅÚÇÏÉ ÊÚÑíİ ãÔÛá ÇáÅÎÑÇÌ
    x.Output(out); // ÅÎÑÇÌ ÚäÇÕÑ ÇáÓáÓáÉ
    return out; // ÅÑÌÇÚ ÏİŞ ÇáÅÎÑÇÌ
}

template<class T>
void Chain<T>::Clear() { // ÍĞİ ÌãíÚ ÇáÚŞÏ
    while (first) { // ÇÌÊíÇÒ ÇáÓáÓáÉ æÍĞİ ÇáÚŞÏ
        ChainNode<T>* temp = first; // ÍİÙ ÇáÚŞÏÉ ÇáÍÇáíÉ
        first = first->link; // ÇáÇäÊŞÇá Åáì ÇáÚŞÏÉ ÇáÊÇáíÉ
        delete temp; // ÍĞİ ÇáÚŞÏÉ ÇáÍÇáíÉ
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

    buttonLayout->addWidget(addButton); // ÅÖÇİÉ ÒÑ "Add Number" Åáì ÇáÊÎØíØ ÇáÃİŞí ááÃÒÑÇÑ (buttonLayout)
    buttonLayout->addWidget(deleteButton); // ÅÖÇİÉ ÒÑ "Delete Number" Åáì ÇáÊÎØíØ ÇáÃİŞí ááÃÒÑÇÑ (buttonLayout)
    buttonLayout->addWidget(searchButton); // ÅÖÇİÉ ÒÑ "Search Number" Åáì ÇáÊÎØíØ ÇáÃİŞí ááÃÒÑÇÑ (buttonLayout)
    buttonLayout->addWidget(maxButton); // ÅÖÇİÉ ÒÑ "Find Second Maximum" Åáì ÇáÊÎØíØ ÇáÃİŞí ááÃÒÑÇÑ (buttonLayout)
    buttonLayout->addWidget(findButton); // ÅÖÇİÉ ÒÑ "Find Position" Åáì ÇáÊÎØíØ ÇáÃİŞí ááÃÒÑÇÑ (buttonLayout)
    buttonLayout->addWidget(lengthButton); // ÅÖÇİÉ ÒÑ "List Length" Åáì ÇáÊÎØíØ ÇáÃİŞí ááÃÒÑÇÑ (buttonLayout)
    buttonLayout->addWidget(clearButton); // ÅÖÇİÉ ÒÑ "Clear All" Åáì ÇáÊÎØíØ ÇáÃİŞí ááÃÒÑÇÑ (buttonLayout)
    buttonLayout->addWidget(trashButton); // ÅÖÇİÉ ÒÑ "Show Trash" Åáì ÇáÊÎØíØ ÇáÃİŞí ááÃÒÑÇÑ (buttonLayout)

    buttonPanel->setLayout(buttonLayout); // Êã ÊÚííä ÇáÊÎØíØ ÇáĞí íÍÊæí Úáì ÇáÃÒÑÇÑ Åáì ÇáÜ buttonPanel

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


    // ÚäÏ ÇáÖÛØ Úáì ÒÑ ÇáÅÖÇİÉ
    QObject::connect(addButton, &QPushButton::clicked, [&]() {
        bool ok;
        int number = inputField->text().toInt(&ok);  // ÊÍæíá ÇáäÕ ÇáãÏÎá Åáì ÑŞã ÕÍíÍ
        int position = positionField->text().isEmpty() ? listWidget->count() + 1 : positionField->text().toInt(&ok); // ÊÍÏíÏ ãæÖÚ ÇáÅÖÇİÉ
        if (ok) {
            try {
                chain.Insert(position, number);  // ÅÏÎÇá ÇáÑŞã İí ÇáÓáÓáÉ
                listWidget->insertItem(position - 1, QString::number(number)); // ÅÖÇİÉ ÇáÑŞã Åáì æÇÌåÉ ÇáŞÇÆãÉ İí ÇáãæÖÚ ÇáãÍÏÏ
                inputField->clear();            // ãÓÍ ÍŞá ÇáÅÏÎÇá
                positionField->clear();         // ãÓÍ ÍŞá ÇáãæÖÚ
            }
            catch (const out_of_range& e) {
                QMessageBox::warning(&window, "Insert Error", e.what());  // ÅÙåÇÑ ÑÓÇáÉ ÎØÃ ÅĞÇ İÔáÊ ÇáÅÖÇİÉ
            }
        }
        else {
            QMessageBox::warning(&window, "Input Error", "Please enter valid data."); // ÅÙåÇÑ ÊÍĞíÑ ÅĞÇ ßÇä ÇáÅÏÎÇá ÛíÑ ÕÍíÍ
        }
        });

    // ÚäÏ ÇáÖÛØ Úáì ÒÑ ÇáÍĞİ
    QObject::connect(deleteButton, &QPushButton::clicked, [&]() {
        QListWidgetItem* selectedItem = listWidget->currentItem();  // ÇáÍÕæá Úáì ÇáÚäÕÑ ÇáãÍÏÏ ÍÇáíÇğ İí ÇáŞÇÆãÉ
        if (selectedItem) {
            int index = listWidget->row(selectedItem) + 1;  // ÇáÍÕæá Úáì İåÑÓ ÇáÚäÕÑ ÇáãÍÏÏ
            try {
                chain.Delete(index, lastDeleted);           // ÍĞİ ÇáÚäÕÑ ãä ÇáÓáÓáÉ
                delete listWidget->takeItem(index - 1);     // ÅÒÇáÉ ÇáÚäÕÑ ãä æÇÌåÉ ÇáŞÇÆãÉ
                deletedNumbers.append(lastDeleted);        // ÅÖÇİÉ ÇáÑŞã ÇáãÍĞæİ Åáì ŞÇÆãÉ ÇáÃÑŞÇã ÇáãÍĞæİÉ
            }
            catch (const out_of_range& e) {
                QMessageBox::warning(&window, "Delete Error", e.what());  // ÅÙåÇÑ ÑÓÇáÉ ÎØÃ ÅĞÇ İÔá ÇáÍĞİ
            }
        }
        else {
            QMessageBox::warning(&window, "Selection Error", "Please select a number to delete."); // ÅÙåÇÑ ÊÍĞíÑ ÅĞÇ áã íÊã ÊÍÏíÏ ÚäÕÑ
        }
        });

    // ÚäÏ ÇáÖÛØ Úáì ÒÑ ÚÑÖ ÇáÚäÇÕÑ ÇáãÍĞæİÉ
    QObject::connect(trashButton, &QPushButton::clicked, [&]() {
        trashListWidget->clear();                          // ãÓÍ ãÍÊæíÇÊ æÇÌåÉ ÓáÉ ÇáãÍĞæİÇÊ
        for (int num : deletedNumbers) {
            trashListWidget->addItem(QString::number(num)); // ÅÖÇİÉ ÌãíÚ ÇáÃÑŞÇã ÇáãÍĞæİÉ Åáì æÇÌåÉ ÓáÉ ÇáãÍĞæİÇÊ
        }
        trashListWidget->show();                           // ÚÑÖ æÇÌåÉ ÓáÉ ÇáãÍĞæİÇÊ
        });

    // ÚäÏ ÇáÖÛØ Úáì ÒÑ ÇáÈÍË
    QObject::connect(searchButton, &QPushButton::clicked, [&]() {
        bool ok;
        int number = inputField->text().toInt(&ok);        // ÊÍæíá ÇáäÕ ÇáãÏÎá Åáì ÑŞã ÕÍíÍ
        if (ok) {
            int position = chain.Search(number);           // ÇáÈÍË Úä ÇáÑŞã İí ÇáÓáÓáÉ
            if (position > 0) {
                resultLabel->setText("Number found at position: " + QString::number(position)); // ÚÑÖ ÇáãæÖÚ ÅĞÇ Êã ÇáÚËæÑ Úáì ÇáÑŞã
            }
            else {
                resultLabel->setText("Number not found."); // ÇáÅÔÇÑÉ Åáì Ãä ÇáÑŞã ÛíÑ ãæÌæÏ
            }
        }
        else {
            QMessageBox::warning(&window, "Input Error", "Please enter a valid number to search."); // ÅÙåÇÑ ÊÍĞíÑ ÅĞÇ ßÇä ÇáÅÏÎÇá ÛíÑ ÕÍíÍ
        }
        });

    // ÚäÏ ÇáÖÛØ Úáì ÒÑ ÅíÌÇÏ ËÇäí ÃßÈÑ ŞíãÉ
    QObject::connect(maxButton, &QPushButton::clicked, [&]() {
        try {
            int secondMax = chain.Max_Second();            // ÇáÍÕæá Úáì ËÇäí ÃßÈÑ ŞíãÉ İí ÇáÓáÓáÉ
            resultLabel->setText("Second maximum: " + QString::number(secondMax)); // ÚÑÖ ËÇäí ÃßÈÑ ŞíãÉ
        }
        catch (const runtime_error& e) {
            resultLabel->setText("Error: " + QString(e.what())); // ÅÙåÇÑ ÑÓÇáÉ ÎØÃ ÅĞÇ ÍÏË ÇÓÊËäÇÁ
        }
        });

    // ÚäÏ ÇáÖÛØ Úáì ÒÑ ãÓÍ ÇáŞÇÆãÉ
    QObject::connect(clearButton, &QPushButton::clicked, [&]() {
        chain.Clear();                                     // ãÓÍ ãÍÊæíÇÊ ÇáÓáÓáÉ
        listWidget->clear();                               // ãÓÍ ãÍÊæíÇÊ æÇÌåÉ ÇáŞÇÆãÉ
        trashListWidget->hide();                           // ÅÎİÇÁ æÇÌåÉ ÓáÉ ÇáãÍĞæİÇÊ
        resultLabel->setText("All items cleared.");        // ÇáÅÔÇÑÉ Åáì Ãäå Êã ãÓÍ ÌãíÚ ÇáÚäÇÕÑ
        });

    // ÚäÏ ÇáÖÛØ Úáì ÒÑ ÅíÌÇÏ ŞíãÉ İí ãæÖÚ ãÍÏÏ
    QObject::connect(findButton, &QPushButton::clicked, [&]() {
        bool ok;
        int position = positionField->text().toInt(&ok);   // ÊÍæíá ÇáÅÏÎÇá İí ÍŞá ÇáãæÖÚ Åáì ÑŞã ÕÍíÍ
        if (ok) {
            int value;
            if (chain.Find(position, value)) {             // ÇáÈÍË Úä ÇáŞíãÉ İí ÇáãæÖÚ ÇáãÍÏÏ
                resultLabel->setText("Value at position " + QString::number(position) + ": " + QString::number(value)); // ÚÑÖ ÇáŞíãÉ
            }
            else {
                resultLabel->setText("No value found at position " + QString::number(position)); // ÇáÅÔÇÑÉ Åáì Ãäå áã íÊã ÇáÚËæÑ Úáì ŞíãÉ
            }
        }
        else {
            QMessageBox::warning(&window, "Input Error", "Please enter a valid position."); // ÅÙåÇÑ ÊÍĞíÑ ÅĞÇ ßÇä ÇáÅÏÎÇá ÛíÑ ÕÍíÍ
        }
        });

    // ÚäÏ ÇáÖÛØ Úáì ÒÑ ÚÑÖ Øæá ÇáŞÇÆãÉ
    QObject::connect(lengthButton, &QPushButton::clicked, [&]() {
        resultLabel->setText("List length: " + QString::number(chain.Length())); // ÚÑÖ Øæá ÇáÓáÓáÉ
        });

    window.setLayout(layout);                               // ÖÈØ ÇáÊÎØíØ ááäÇİĞÉ ÇáÑÆíÓíÉ
    window.show();                                          // ÚÑÖ ÇáäÇİĞÉ ÇáÑÆíÓíÉ

    return app.exec();                                      // ÊäİíĞ ÇáÊØÈíŞ

}
