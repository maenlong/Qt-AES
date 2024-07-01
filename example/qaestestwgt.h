#ifndef QAESTESTWGT_H
#define QAESTESTWGT_H

#include <QWidget>
#include "qaesencryption.h"

namespace Ui {
class qAesTestWgt;
}

class qAesTestWgt : public QWidget
{
    Q_OBJECT

public:
    explicit qAesTestWgt(QWidget *parent = nullptr);
    ~qAesTestWgt();


    struct AesCodeData{
        QString source = "";
        QString key = "";
        QString iv = "";
        QAESEncryption::Aes aes = QAESEncryption::AES_128;
        QAESEncryption::Mode mode = QAESEncryption::ECB;
        QAESEncryption::Padding padding = QAESEncryption::ZERO;
    };

    void initTest();    //初始化测试，原程序启动入口示例

    //字符串加密
    QString encodeStr(AesCodeData data);

    //字符串解密
    QString decodeStr(AesCodeData data);

private slots:
    void on_generateBtn_clicked(bool checked);      //执行加解密
    void on_resetBtn_clicked(bool checked);         //各选项重置

private:
    Ui::qAesTestWgt *ui;
};

#endif // QAESTESTWGT_H
