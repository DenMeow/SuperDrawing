#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : //конструктор
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Рисуночки Дмитрия Анатольевича");
    ui->widget->create_im(ui->widget->width(),ui->widget->height()); //создаем изображение на котором сможем рисовать
    ui->tableWidget->setColumnCount(KOL_COL);
    ui->tableWidget->setRowCount(0);
    ui->spinBox->setValue(0);
    obj_data = nullptr;
}

MainWindow::~MainWindow() //деструктор
{
    delete ui;
}

void MainWindow::on_spinBox_valueChanged(int arg1) //изменено количество элементов
{
    int need_rows = arg1 * 2; //каждый графический элемент требует 2 строки
    int cur_rows = ui->tableWidget->rowCount();
    int old_val = cur_rows/2;
    if (cur_rows < 0)
        cur_rows = 0;

    if (need_rows > cur_rows) //добавляем строки
    {
        ui->tableWidget->setRowCount(need_rows);
        int i = cur_rows;
        QTableWidgetItem * twi;
        QComboBox * cb;
        while (i<need_rows)
        {
            twi = new QTableWidgetItem;
            twi->setText("Объект");
            twi->setFlags(twi->flags()&0xfffffffd); //сброс флага разрешения редактирования
            ui->tableWidget->setItem(i,0,twi);

            twi = new QTableWidgetItem;
            twi->setText("X");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->setItem(i,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->setItem(i,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("Настройки");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->setItem(i,3,twi);

            for (int j=4;j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xfffffffd);
                ui->tableWidget->setItem(i,j,twi);
            }
            i++;

            cb = new QComboBox;
            cb->addItem("Точка");
            cb->addItem("Линия");
            cb->addItem("Прямоугольник");
            cb->addItem("Окружность");
            cb->addItem("Эллипс");
            cb->addItem("Треугольник");
            cb->addItem("Дуга");
            cb->addItem("Сегмент");
            cb->addItem("Сектор");
            cb->addItem("Ломанная");
            cb->addItem("Полигон");

            cb->setProperty("row",i);
            connect(cb,SIGNAL(activated(int)),this,SLOT(Combo_click(int)));
            connect(cb,SIGNAL(currentIndexChanged(int)),this,SLOT(Combo_click(int)));

            ui->tableWidget->setCellWidget(i,0,cb);//так как точка по умолчаниию

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->setItem(i,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->setItem(i,2,twi);

            QPushButton * pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",i);
            connect(pb,SIGNAL(clicked()),this,SLOT(style_click()));

            ui->tableWidget->setCellWidget(i,3,pb);

            for (int j=4;j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xfffffffd);
                ui->tableWidget->setItem(i,j,twi);
            }
            i++;
        }
    }
    else  //удаляем строки
    {
        ui->tableWidget->setRowCount(need_rows);
    }

    if (arg1<=0)
    {
        delete [] obj_data;
        obj_data=nullptr;
    }
    else
    {
        //        if ((old_val==0)||(obj_data==nullptr))
        //            obj_data=new T_OBJ_DATA[arg1];
        if (old_val<arg1)
        {
            //добавляем
            if (((old_val==0)||(obj_data==nullptr)))
                obj_data=new T_OBJ_DATA[arg1];
            else
            {
                T_OBJ_DATA * n_obj_data=obj_data; //сохранили старое значение
                obj_data=new T_OBJ_DATA[arg1]; //выделяем память под новые данные
                memcpy(obj_data,n_obj_data,old_val*sizeof (T_OBJ_DATA)); //скопировали старые данные
                delete []  n_obj_data;
            }
            //инициализация значений
            for (int i = old_val;i < arg1;i++)
            {
                //установка дефолтных значений
                obj_data[i].kol = 0;
                obj_data[i].mas = nullptr;
                obj_data[i].my_pen.SetStyle(1);
                obj_data[i].my_pen.SetStyleBrush(1);
                obj_data[i].my_pen.SetRGBA(255,255,255,255);
                obj_data[i].my_pen.SetRGBA_brush(255,255,255,255);
                obj_data[i].my_pen.SetWidth(1);
            }
        }
        else
        {
            //Удаляем
            T_OBJ_DATA * n_obj_data=obj_data; //сохранили старое значение
            if (arg1>0)
            {
                obj_data=new T_OBJ_DATA[arg1]; //выделяем память под новые данные
                memcpy(obj_data,n_obj_data,arg1*sizeof (T_OBJ_DATA)); //скопировали
                //нужное количество старых данных
            }
            else
            {
                obj_data=nullptr;
                arg1=0;
            }
            for (int i=arg1;i<old_val;i++)
            {
                //освобождаем память внутри дочерних структур
                if (n_obj_data[i].kol>0)
                    delete [] n_obj_data[i].mas;
            }
            delete []  n_obj_data;
        }
    }
}

void MainWindow::Combo_click(int arg1)  //смена типа фигуры
{
    int row;
    QComboBox *cbox = qobject_cast<QComboBox *>(sender());

    if (cbox!=nullptr)
    {
        row = cbox->property("row").toInt();

        QTableWidgetItem * twi;

        //инициализация значений
        int indx = (row-1)/2;
        if (obj_data[indx].kol>0)
        {
            //установка дефолтных значений при выборе новой фигуры
            delete [] obj_data[indx].mas;
            obj_data[indx].kol=0;
            obj_data[indx].mas=nullptr;
            obj_data[indx].my_pen.SetStyle(1);
            obj_data[indx].my_pen.SetStyleBrush(1);
            obj_data[indx].my_pen.SetRGBA(255,255,255,255);
            obj_data[indx].my_pen.SetRGBA_brush(255,255,255,255);
            obj_data[indx].my_pen.SetWidth(1);
        }

        switch (arg1)
        {
        case 0: //точка
        {
            int row_m=row-1;

            //строка подписей
            twi = new QTableWidgetItem;
            twi->setText("X");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,1);
            ui->tableWidget->setItem(row_m,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,2);
            ui->tableWidget->setItem(row_m,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("Настройки");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,3);
            ui->tableWidget->setItem(row_m,3,twi);

            for (int j=4;j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xfffffffd);
                ui->tableWidget->removeCellWidget(row_m,j);
                ui->tableWidget->setItem(row_m,j,twi);
            }

            //строка значений

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setItem(row,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setItem(row,2,twi);

            QPushButton * pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(style_click()));

            ui->tableWidget->removeCellWidget(row,3);
            ui->tableWidget->setCellWidget(row,3,pb);

            for (int j=4;j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xfffffffd);
                ui->tableWidget->removeCellWidget(row,j);
                ui->tableWidget->setItem(row,j,twi);
            }

            break;

        }
        case 1: //линия
        {
            int row_m=row-1;

            //строка подписей
            twi = new QTableWidgetItem;
            twi->setText("X1");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,1);
            ui->tableWidget->setItem(row_m,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y1");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,2);
            ui->tableWidget->setItem(row_m,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("X2");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,3);
            ui->tableWidget->setItem(row_m,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y2");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,4);
            ui->tableWidget->setItem(row_m,4,twi);

            twi = new QTableWidgetItem;
            twi->setText("Настройки");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,5);
            ui->tableWidget->setItem(row_m,5,twi);

            for (int j=6;j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xfffffffd);
                ui->tableWidget->removeCellWidget(row_m,j);
                ui->tableWidget->setItem(row_m,j,twi);
            }

            //строка значений

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setItem(row,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setItem(row,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,3);
            ui->tableWidget->setItem(row,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,4);
            ui->tableWidget->setItem(row,4,twi);

            QPushButton * pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(style_click()));

            ui->tableWidget->removeCellWidget(row,5);
            ui->tableWidget->setCellWidget(row,5,pb);

            for (int j=6;j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xfffffffd);
                ui->tableWidget->removeCellWidget(row,j);
                ui->tableWidget->setItem(row,j,twi);
            }

            break;

        }
        case 2: //Прямоугольник
        {
            int row_m=row-1;

            //строка подписей
            twi = new QTableWidgetItem;
            twi->setText("X1");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,1);
            ui->tableWidget->setItem(row_m,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y1");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,2);
            ui->tableWidget->setItem(row_m,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("X2");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,3);
            ui->tableWidget->setItem(row_m,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y2");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,4);
            ui->tableWidget->setItem(row_m,4,twi);

            twi = new QTableWidgetItem;
            twi->setText("Настройки");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,5);
            ui->tableWidget->setItem(row_m,5,twi);

            for (int j=6;j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xfffffffd);
                ui->tableWidget->removeCellWidget(row_m,j);
                ui->tableWidget->setItem(row_m,j,twi);
            }

            //строка значений

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setItem(row,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setItem(row,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,3);
            ui->tableWidget->setItem(row,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,4);
            ui->tableWidget->setItem(row,4,twi);

            QPushButton * pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(style_click()));

            ui->tableWidget->removeCellWidget(row,5);
            ui->tableWidget->setCellWidget(row,5,pb);

            for (int j=6;j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xfffffffd);
                ui->tableWidget->removeCellWidget(row,j);
                ui->tableWidget->setItem(row,j,twi);
            }

            break;

        }
        case 3: //окружность
        {
            int row_m=row-1;

            //строка подписей
            twi = new QTableWidgetItem;
            twi->setText("X");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,1);
            ui->tableWidget->setItem(row_m,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,2);
            ui->tableWidget->setItem(row_m,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("Радиус");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,3);
            ui->tableWidget->setItem(row_m,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("Настройки");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,4);
            ui->tableWidget->setItem(row_m,4,twi);

            for (int j=5;j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xfffffffd);
                ui->tableWidget->removeCellWidget(row_m,j);
                ui->tableWidget->setItem(row_m,j,twi);
            }

            //строка значений

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setItem(row,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setItem(row,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,3);
            ui->tableWidget->setItem(row,3,twi);

            QPushButton * pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(style_click()));

            ui->tableWidget->removeCellWidget(row,4);
            ui->tableWidget->setCellWidget(row,4,pb);

            for (int j=5;j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xfffffffd);
                ui->tableWidget->removeCellWidget(row,j);
                ui->tableWidget->setItem(row,j,twi);
            }

            break;

        }
        case 4: //эллипс
        {
            int row_m=row-1;

            //строка подписей
            twi = new QTableWidgetItem;
            twi->setText("X");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,1);
            ui->tableWidget->setItem(row_m,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,2);
            ui->tableWidget->setItem(row_m,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("Горизонт. радиус");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,3);
            ui->tableWidget->setItem(row_m,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("Верт. радиус");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,4);
            ui->tableWidget->setItem(row_m,4,twi);

            twi = new QTableWidgetItem;
            twi->setText("Настройки");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,5);
            ui->tableWidget->setItem(row_m,5,twi);

            for (int j=6;j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xfffffffd);
                ui->tableWidget->removeCellWidget(row_m,j);
                ui->tableWidget->setItem(row_m,j,twi);
            }

            //строка значений

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setItem(row,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setItem(row,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,3);
            ui->tableWidget->setItem(row,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,4);
            ui->tableWidget->setItem(row,4,twi);

            QPushButton * pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(style_click()));

            ui->tableWidget->removeCellWidget(row,5);
            ui->tableWidget->setCellWidget(row,5,pb);

            for (int j=6;j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xfffffffd);
                ui->tableWidget->removeCellWidget(row,j);
                ui->tableWidget->setItem(row,j,twi);
            }

            break;

        }
        case 5: //треугольник
        {
            int row_m=row-1;

            //строка подписей
            twi = new QTableWidgetItem;
            twi->setText("X1");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,1);
            ui->tableWidget->setItem(row_m,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y1");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,2);
            ui->tableWidget->setItem(row_m,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("X2");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,3);
            ui->tableWidget->setItem(row_m,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y2");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,4);
            ui->tableWidget->setItem(row_m,4,twi);

            twi = new QTableWidgetItem;
            twi->setText("X3");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,5);
            ui->tableWidget->setItem(row_m,5,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y3");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,6);
            ui->tableWidget->setItem(row_m,6,twi);

            twi = new QTableWidgetItem;
            twi->setText("Настройки");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,7);
            ui->tableWidget->setItem(row_m,7,twi);

            //строка значений

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setItem(row,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setItem(row,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,3);
            ui->tableWidget->setItem(row,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,4);
            ui->tableWidget->setItem(row,4,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,5);
            ui->tableWidget->setItem(row,5,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,6);
            ui->tableWidget->setItem(row,6,twi);

            QPushButton * pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(style_click()));

            ui->tableWidget->removeCellWidget(row,7);
            ui->tableWidget->setCellWidget(row,7,pb);

            break;

        }
        case 6: //дуга
        {
            int row_m=row-1;

            //строка подписей
            twi = new QTableWidgetItem;
            twi->setText("X");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,1);
            ui->tableWidget->setItem(row_m,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,2);
            ui->tableWidget->setItem(row_m,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("Горизонт. радиус");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,3);
            ui->tableWidget->setItem(row_m,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("Верт. радиус");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,4);
            ui->tableWidget->setItem(row_m,4,twi);

            twi = new QTableWidgetItem;
            twi->setText("Начальный угол°");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,5);
            ui->tableWidget->setItem(row_m,5,twi);

            twi = new QTableWidgetItem;
            twi->setText("Конечный угол°");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,6);
            ui->tableWidget->setItem(row_m,6,twi);

            twi = new QTableWidgetItem;
            twi->setText("Настройки");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,7);
            ui->tableWidget->setItem(row_m,7,twi);

            //строка значений

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setItem(row,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setItem(row,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,3);
            ui->tableWidget->setItem(row,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,4);
            ui->tableWidget->setItem(row,4,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,5);
            ui->tableWidget->setItem(row,5,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,6);
            ui->tableWidget->setItem(row,6,twi);

            QPushButton * pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(style_click()));

            ui->tableWidget->removeCellWidget(row,7);
            ui->tableWidget->setCellWidget(row,7,pb);

            break;

        }
        case 7: //хорда
        {
            int row_m=row-1;

            //строка подписей
            twi = new QTableWidgetItem;
            twi->setText("X");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,1);
            ui->tableWidget->setItem(row_m,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,2);
            ui->tableWidget->setItem(row_m,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("Горизонт. радиус");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,3);
            ui->tableWidget->setItem(row_m,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("Верт. радиус");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,4);
            ui->tableWidget->setItem(row_m,4,twi);

            twi = new QTableWidgetItem;
            twi->setText("Начальный угол°");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,5);
            ui->tableWidget->setItem(row_m,5,twi);

            twi = new QTableWidgetItem;
            twi->setText("Конечный угол°");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,6);
            ui->tableWidget->setItem(row_m,6,twi);

            twi = new QTableWidgetItem;
            twi->setText("Настройки");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,7);
            ui->tableWidget->setItem(row_m,7,twi);

            //строка значений

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setItem(row,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setItem(row,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,3);
            ui->tableWidget->setItem(row,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,4);
            ui->tableWidget->setItem(row,4,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,5);
            ui->tableWidget->setItem(row,5,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,6);
            ui->tableWidget->setItem(row,6,twi);

            QPushButton * pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(style_click()));

            ui->tableWidget->removeCellWidget(row,7);
            ui->tableWidget->setCellWidget(row,7,pb);

            break;

        }
        case 8: //хорда
        {
            int row_m=row-1;

            //строка подписей
            twi = new QTableWidgetItem;
            twi->setText("X");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,1);
            ui->tableWidget->setItem(row_m,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,2);
            ui->tableWidget->setItem(row_m,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("Горизонт. радиус");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,3);
            ui->tableWidget->setItem(row_m,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("Верт. радиус");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,4);
            ui->tableWidget->setItem(row_m,4,twi);

            twi = new QTableWidgetItem;
            twi->setText("Начальный угол°");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,5);
            ui->tableWidget->setItem(row_m,5,twi);

            twi = new QTableWidgetItem;
            twi->setText("Конечный угол°");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,6);
            ui->tableWidget->setItem(row_m,6,twi);

            twi = new QTableWidgetItem;
            twi->setText("Настройки");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,7);
            ui->tableWidget->setItem(row_m,7,twi);

            //строка значений

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setItem(row,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setItem(row,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,3);
            ui->tableWidget->setItem(row,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,4);
            ui->tableWidget->setItem(row,4,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,5);
            ui->tableWidget->setItem(row,5,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем и делаем пустую строку
            ui->tableWidget->removeCellWidget(row,6);
            ui->tableWidget->setItem(row,6,twi);

            QPushButton * pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(style_click()));

            ui->tableWidget->removeCellWidget(row,7);
            ui->tableWidget->setCellWidget(row,7,pb);

            break;

        }
        case 9: //Ломаная
        {
            int row_m=row-1;

            //строка подписей

            twi = new QTableWidgetItem;
            twi->setText("Координаты");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,1);
            ui->tableWidget->setItem(row_m,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Настройки");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,2);
            ui->tableWidget->setItem(row_m,2,twi);

            for (int j=3;j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xfffffffd);
                ui->tableWidget->removeCellWidget(row_m,j);
                ui->tableWidget->setItem(row_m,j,twi);
            }

            //строка значений

            QPushButton * pb = new QPushButton(this);
            pb->setText("Точки");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(points_click()));

            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setCellWidget(row,1,pb);

            pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(style_click()));

            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setCellWidget(row,2,pb);

            for (int j=3;j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xfffffffd);
                ui->tableWidget->removeCellWidget(row,j);
                ui->tableWidget->setItem(row,j,twi);
            }

            break;

        }
        case 10: //Полигон
        {
            int row_m=row-1;

            //строка подписей

            twi = new QTableWidgetItem;
            twi->setText("Координаты");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,1);
            ui->tableWidget->setItem(row_m,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Настройки");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(row_m,2);
            ui->tableWidget->setItem(row_m,2,twi);

            for (int j=3;j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xfffffffd);
                ui->tableWidget->removeCellWidget(row_m,j);
                ui->tableWidget->setItem(row_m,j,twi);
            }

            //строка значений

            QPushButton * pb = new QPushButton(this);
            pb->setText("Точки");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(points_click()));

            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setCellWidget(row,1,pb);

            pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(style_click()));

            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setCellWidget(row,2,pb);

            for (int j=3;j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xfffffffd);
                ui->tableWidget->removeCellWidget(row,j);
                ui->tableWidget->setItem(row,j,twi);
            }

            break;

        }
        }
    }

}

void MainWindow::style_click(void) //диалоговое окно настроек
{
    QPushButton * pb = qobject_cast<QPushButton *>(sender());
    if (pb!=nullptr)
    {
        int row = pb->property("row").toInt();
        int indx=(row-1)/2;
        Dialog_style dial;

        QComboBox * cb =  qobject_cast<QComboBox *>(ui->tableWidget->cellWidget(row,0));
        if(cb == nullptr){
            return;
        }

        dial.setStyleVisible(cb->currentIndex()!=0);
        if (cb->currentIndex()==0 or cb->currentIndex()==1 or cb->currentIndex()==6 or cb->currentIndex()==9){
            dial.setStyleBrushVisible(0);
        }
        else{
            dial.setStyleBrushVisible(1);
        }

        mpen my_pen;

        //получить предыдущие значения из диалога
        int r_l,g_l,b_l,a_l,r_b,g_b,b_b,a_b;
        obj_data[indx].my_pen.GetRGBA(r_l,g_l,b_l,a_l);
        obj_data[indx].my_pen.GetRGBA_brush(r_b,g_b,b_b,a_b);
        my_pen.SetRGBA(r_l,g_l,b_l,a_l);
        my_pen.SetRGBA_brush(r_b,g_b,b_b,a_b);
        my_pen.SetStyle(obj_data[indx].my_pen.GetStyle());
        my_pen.SetStyleBrush(obj_data[indx].my_pen.GetStyleBrush());
        my_pen.SetWidth(obj_data[indx].my_pen.GetWidth());

        dial.setValue(my_pen);

        if (dial.exec() == 1)
        {
            //сохранить значения из диалога
            dial.GetRGBA(r_l,g_l,b_l,a_l);
            obj_data[indx].my_pen.SetRGBA(r_l,g_l,b_l,a_l);

            dial.GetRGBA_brush(r_b,g_b,b_b,a_b);
            obj_data[indx].my_pen.SetRGBA_brush(r_b,g_b,b_b,a_b);

            obj_data[indx].my_pen.SetStyle(dial.GetStyle());
            obj_data[indx].my_pen.SetStyleBrush(dial.GetStyleBrush());
            obj_data[indx].my_pen.SetWidth(dial.GetWidth());
        }
    }
}

void MainWindow::points_click() //диалоговое окно выбора координат для точек в polyline / polygon
{
    QPushButton * pb = qobject_cast<QPushButton *>(sender());
    if (pb!=nullptr)
    {
        int row = pb->property("row").toInt();
        int indx=(row-1)/2;

        Dialog_points dial;

        dial.setValue(obj_data[indx].kol,obj_data[indx].mas);

        dial.exec();

        int kol;
        int *p_mas=nullptr;
        if (dial.getValue(kol,p_mas))
        {
            obj_data[indx].kol=kol;
            delete [] obj_data[indx].mas;
            obj_data[indx].mas=p_mas;
        }
    }
}

void MainWindow::on_pushButton_draw_clicked() //рисуем рисуночки
{
    on_pushButton_clear_clicked();
    int row_count = ui->tableWidget->rowCount();

    for (int i = 1; i < row_count; i+=2)
    {
        QComboBox *comboBox = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i, 0));
        QString selectedType = comboBox->currentText();

        int indx=(i-1)/2;
        if(selectedType == "Точка"){
            int x,y;
            QString str;
            bool flag;
            pixel m_p; //мой пиксель

            str.clear();

            str.append(ui->tableWidget->item(i,1)->text());
            x=str.toInt(&flag);
            if(!flag or x < -32000 or x > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты X [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,2)->text());
            y=str.toInt(&flag);
            if(!flag or y < -32000 or y > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Y [-32000;32000]");
                correct_value = false;

                return;
            }
            int r_l,g_l,b_l,a_l;
            obj_data[indx].my_pen.GetRGBA(r_l,g_l,b_l,a_l);
            m_p.pen.SetRGBA(r_l,g_l,b_l,a_l);
            m_p.pen.SetWidth(obj_data[indx].my_pen.GetWidth());

            m_p.SetX(x);
            m_p.SetY(y);
            m_p.draw(ui->widget->im);

            update();
        }
        else if(selectedType == "Линия"){
            int x1,y1,x2,y2;
            QString str;
            bool flag;
            line m_l; //моя линия

            str.clear();

            str.append(ui->tableWidget->item(i,1)->text());
            x1 = str.toInt(&flag);
            if(!flag or x1 < -32000 or x1 > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты X1 [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,2)->text());
            y1 = str.toInt(&flag);
            if(!flag or y1 < -32000 or y1 > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Y1 [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,3)->text());
            x2 = str.toInt(&flag);
            if(!flag or x2 < -32000 or x2 > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты X2 [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,4)->text());
            y2 = str.toInt(&flag);
            if(!flag or y2 < -32000 or y2 > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Y2 [-32000;32000]");
                correct_value = false;
                return;
            }
            int r_l,g_l,b_l,a_l;
            obj_data[indx].my_pen.GetRGBA(r_l,g_l,b_l,a_l);
            m_l.pen.SetRGBA(r_l,g_l,b_l,a_l);
            m_l.pen.SetWidth(obj_data[indx].my_pen.GetWidth());
            m_l.pen.SetStyle(obj_data[indx].my_pen.GetStyle());

            m_l.st.SetX(x1);
            m_l.st.SetY(y1);
            m_l.end.SetX(x2);
            m_l.end.SetY(y2);
            m_l.draw(ui->widget->im);
            update();
        }
        else if(selectedType == "Прямоугольник"){
            int x1,y1,x2,y2;
            QString str;
            bool flag;
            mrect m_r; //мой прямоугольник

            str.clear();

            str.append(ui->tableWidget->item(i,1)->text());
            x1 = str.toInt(&flag);
            if(!flag or x1 < -32000 or x1 > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты X1 [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,2)->text());
            y1 = str.toInt(&flag);
            if(!flag or y1 < -32000 or y1 > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Y1 [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,3)->text());
            x2 = str.toInt(&flag);
            if(!flag or x2 < -32000 or x2 > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты X2 [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,4)->text());
            y2 = str.toInt(&flag);
            if(!flag or y2 < -32000 or y2 > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Y2 [-32000;32000]");
                correct_value = false;
                return;
            }
            int r_l,g_l,b_l,a_l, r_b, g_b, b_b, a_b;
            obj_data[indx].my_pen.GetRGBA(r_l,g_l,b_l,a_l);
            obj_data[indx].my_pen.GetRGBA_brush(r_b,g_b,b_b,a_b);
            m_r.pen.SetRGBA(r_l,g_l,b_l,a_l);
            m_r.pen.SetWidth(obj_data[indx].my_pen.GetWidth());
            m_r.pen.SetStyle(obj_data[indx].my_pen.GetStyle());
            m_r.pen.SetStyleBrush(obj_data[indx].my_pen.GetStyleBrush());

            m_r.pen.SetRGBA_brush(r_b,g_b,b_b,a_b);

            m_r.left_top.SetX(x1);
            m_r.left_top.SetY(y1);
            m_r.right_bottom.SetX(x2);
            m_r.right_bottom.SetY(y2);
            m_r.draw(ui->widget->im);
            update();
        }
        else if(selectedType == "Окружность"){
            int x, y, r;
            QString str;
            bool flag;
            circle m_c; //мой круг

            str.clear();

            str.append(ui->tableWidget->item(i,1)->text());
            x = str.toInt(&flag);
            if(!flag or x < -32000 or x > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты X [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,2)->text());
            y = str.toInt(&flag);
            if(!flag or y < -32000 or y > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Y [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,3)->text());
            r = str.toInt(&flag);
            if(!flag or r < 0 or r > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Радиус [0;32000]");
                correct_value = false;
                return;
            }
            int r_l,g_l,b_l,a_l, r_b, g_b, b_b, a_b;
            obj_data[indx].my_pen.GetRGBA(r_l,g_l,b_l,a_l);
            obj_data[indx].my_pen.GetRGBA_brush(r_b,g_b,b_b,a_b);
            m_c.pen.SetRGBA(r_l,g_l,b_l,a_l);
            m_c.pen.SetWidth(obj_data[indx].my_pen.GetWidth());
            m_c.pen.SetStyle(obj_data[indx].my_pen.GetStyle());
            m_c.pen.SetStyleBrush(obj_data[indx].my_pen.GetStyleBrush());

            m_c.pen.SetRGBA_brush(r_b,g_b,b_b,a_b);


            m_c.center.SetX(x);
            m_c.center.SetY(y);
            m_c.radius.SetX(r);
            m_c.draw(ui->widget->im);
            update();
        }
        else if(selectedType == "Эллипс"){
            int x, y,h,w;
            QString str;
            bool flag;
            ellips m_e; //мой эллипс

            str.clear();

            str.append(ui->tableWidget->item(i,1)->text());
            x = str.toInt(&flag);
            if(!flag or x < -32000 or x > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты X [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,2)->text());
            y = str.toInt(&flag);
            if(!flag or y < -32000 or y > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Y [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,3)->text());
            h = str.toInt(&flag);
            if(!flag or h < 0 or h > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Горизонтальный радиус [0;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,4)->text());
            w = str.toInt(&flag);
            if(!flag or w < 0 or w > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Вертикальный радиус [0;32000]");
                correct_value = false;
                return;
            }
            int r_l,g_l,b_l,a_l, r_b, g_b, b_b, a_b;
            obj_data[indx].my_pen.GetRGBA(r_l,g_l,b_l,a_l);
            obj_data[indx].my_pen.GetRGBA_brush(r_b,g_b,b_b,a_b);
            m_e.pen.SetRGBA(r_l,g_l,b_l,a_l);
            m_e.pen.SetWidth(obj_data[indx].my_pen.GetWidth());
            m_e.pen.SetStyle(obj_data[indx].my_pen.GetStyle());
            m_e.pen.SetStyleBrush(obj_data[indx].my_pen.GetStyleBrush());

            m_e.pen.SetRGBA_brush(r_b,g_b,b_b,a_b);


            m_e.center.SetX(x);
            m_e.center.SetY(y);
            m_e.radius.SetX(h);
            m_e.radius.SetY(w);
            m_e.draw(ui->widget->im);
            update();
        }
        else if(selectedType == "Треугольник"){
            int x1,y1,x2,y2,x3,y3;
            QString str;
            bool flag;
            triangle  m_t; //мой треугольник

            str.clear();

            str.append(ui->tableWidget->item(i,1)->text());
            x1 = str.toInt(&flag);
            if(!flag or x1 < -32000 or x1 > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты X1 [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,2)->text());
            y1 = str.toInt(&flag);
            if(!flag or y1 < -32000 or y1 > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Y1 [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,3)->text());
            x2 = str.toInt(&flag);
            if(!flag or x2 < -32000 or x2 > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты X2 [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,4)->text());
            y2 = str.toInt(&flag);
            if(!flag or y2 < -32000 or y2 > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Y2 [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,5)->text());
            x3 = str.toInt(&flag);
            if(!flag or x3 < -32000 or x3 > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты X3 [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,6)->text());
            y3 = str.toInt(&flag);
            if(!flag or y3 < -32000 or y3 > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Y3 [-32000;32000]");
                correct_value = false;
                return;
            }
            int r_l,g_l,b_l,a_l, r_b, g_b, b_b, a_b;
            obj_data[indx].my_pen.GetRGBA(r_l,g_l,b_l,a_l);
            obj_data[indx].my_pen.GetRGBA_brush(r_b,g_b,b_b,a_b);
            m_t.pen.SetRGBA(r_l,g_l,b_l,a_l);
            m_t.pen.SetWidth(obj_data[indx].my_pen.GetWidth());
            m_t.pen.SetStyle(obj_data[indx].my_pen.GetStyle());
            m_t.pen.SetStyleBrush(obj_data[indx].my_pen.GetStyleBrush());

            m_t.pen.SetRGBA_brush(r_b,g_b,b_b,a_b);

            m_t.t1.SetXY(x1,y1);
            m_t.t2.SetXY(x2,y2);
            m_t.t3.SetXY(x3,y3);
            m_t.draw(ui->widget->im);
            update();
        }
        else if(selectedType == "Дуга"){
            int x, y, h, w, st, sp;
            QString str;
            bool flag;
            m_arc m_arc;

            str.clear();

            str.append(ui->tableWidget->item(i,1)->text());
            x = str.toInt(&flag);
            if(!flag or x < -32000 or x > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты X [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,2)->text());
            y = str.toInt(&flag);
            if(!flag or y < -32000 or y > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Y [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,3)->text());
            h = str.toInt(&flag);
            if(!flag or h < 0 or h > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Горизонтальный радиус [0;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,4)->text());
            w = str.toInt(&flag);
            if(!flag or w < 0 or w > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Вертикальный радиус [0;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,5)->text());
            st = str.toInt(&flag);
            if(!flag or st < -360 or st > 360){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Начальный угол°");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,6)->text());
            sp = str.toInt(&flag);
            if(!flag or sp < -360 or sp > 360){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Конечный угол°");
                correct_value = false;
                return;
            }
            int r_l,g_l,b_l,a_l;
            obj_data[indx].my_pen.GetRGBA(r_l,g_l,b_l,a_l);
            m_arc.pen.SetRGBA(r_l,g_l,b_l,a_l);
            m_arc.pen.SetWidth(obj_data[indx].my_pen.GetWidth());
            m_arc.pen.SetStyle(obj_data[indx].my_pen.GetStyle());

            m_arc.center.SetX(x);
            m_arc.center.SetY(y);
            m_arc.radius.SetStRadius(h);
            m_arc.radius2.SetSpRadius(w);
            m_arc.angle.SetAngle(st,sp);
            m_arc.draw(ui->widget->im);
            update();
        }
        else if(selectedType == "Сегмент"){
            int x, y, h, w, st, sp;
            QString str;
            bool flag;
            chord chord;

            str.clear();

            str.append(ui->tableWidget->item(i,1)->text());
            x = str.toInt(&flag);
            if(!flag or x < -32000 or x > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты X [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,2)->text());
            y = str.toInt(&flag);
            if(!flag or y < -32000 or y > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Y [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,3)->text());
            h = str.toInt(&flag);
            if(!flag or h < 0 or h > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Горизонтальный радиус [0;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,4)->text());
            w = str.toInt(&flag);
            if(!flag or w < 0 or w > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Вертикальный радиус [0;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,5)->text());
            st = str.toInt(&flag);
            if(!flag or st < -360 or st > 360){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Начальный угол°");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,6)->text());
            sp = str.toInt(&flag);
            if(!flag or sp < -360 or sp > 360){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Конечный угол°");
                correct_value = false;
                return;
            }
            int r_l,g_l,b_l,a_l, r_b, g_b, b_b, a_b;
            obj_data[indx].my_pen.GetRGBA(r_l,g_l,b_l,a_l);
            obj_data[indx].my_pen.GetRGBA_brush(r_b,g_b,b_b,a_b);
            chord.pen.SetRGBA(r_l,g_l,b_l,a_l);
            chord.pen.SetWidth(obj_data[indx].my_pen.GetWidth());
            chord.pen.SetStyle(obj_data[indx].my_pen.GetStyle());
            chord.pen.SetStyleBrush(obj_data[indx].my_pen.GetStyleBrush());

            chord.pen.SetRGBA_brush(r_b,g_b,b_b,a_b);


            chord.center.SetX(x);
            chord.center.SetY(y);
            chord.radius.SetStRadius(h);
            chord.radius2.SetSpRadius(w);
            chord.angle.SetAngle(st,sp);
            chord.draw(ui->widget->im);
            update();
        }
        else if(selectedType == "Сектор"){
            int x, y, h, w, st, sp;
            QString str;
            bool flag;
            m_pie m_pie;

            str.clear();

            str.append(ui->tableWidget->item(i,1)->text());
            x = str.toInt(&flag);
            if(!flag or x < -32000 or x > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты X [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,2)->text());
            y = str.toInt(&flag);
            if(!flag or y < -32000 or y > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Y [-32000;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,3)->text());
            h = str.toInt(&flag);
            if(!flag or h < 0 or h > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Горизонтальный радиус [0;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,4)->text());
            w = str.toInt(&flag);
            if(!flag or w < 0 or w > 32000){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Вертикальный радиус [0;32000]");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,5)->text());
            st = str.toInt(&flag);
            if(!flag or st < -360 or st > 360){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Начальный угол°");
                correct_value = false;
                return;
            }
            str.clear();

            str.append(ui->tableWidget->item(i,6)->text());
            sp = str.toInt(&flag);
            if(!flag or sp < -360 or sp > 360){
                QMessageBox::information(this,"Ошибка!","Некорректные значения в поле ввода координаты Конечный угол°");
                correct_value = false;
                return;
            }
            int r_l,g_l,b_l,a_l, r_b, g_b, b_b, a_b;
            obj_data[indx].my_pen.GetRGBA(r_l,g_l,b_l,a_l);
            obj_data[indx].my_pen.GetRGBA_brush(r_b,g_b,b_b,a_b);
            m_pie.pen.SetRGBA(r_l,g_l,b_l,a_l);
            m_pie.pen.SetWidth(obj_data[indx].my_pen.GetWidth());
            m_pie.pen.SetStyle(obj_data[indx].my_pen.GetStyle());
            m_pie.pen.SetStyleBrush(obj_data[indx].my_pen.GetStyleBrush());

            m_pie.pen.SetRGBA_brush(r_b,g_b,b_b,a_b);


            m_pie.center.SetX(x);
            m_pie.center.SetY(y);
            m_pie.radius.SetStRadius(h);
            m_pie.radius2.SetSpRadius(w);
            m_pie.angle.SetAngle(st,sp);
            m_pie.draw(ui->widget->im);
            update();
        }
        else if(selectedType == "Ломанная"){
            polyline m_pl; //моя тупая линия
            int *mas = obj_data[indx].mas;
            int **points = new int *[obj_data[indx].kol];
            int cols = 2;

            for(int i = 0; i < obj_data[indx].kol; ++i){
                points[i] = new int[cols];
            }
            for (int i = 0; i < obj_data[indx].kol; ++i) {
                for (int j = 0; j < cols; ++j) {
                    int index = i * cols + j;
                    points[i][j] = mas[index];
                }
            }
            for (int i = 0; i < obj_data[indx].kol; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if(j == 0){
                        m_pl.point.setX(points[i][j]);
                    }
                    else{
                        m_pl.point.setY(points[i][j]);
                    }
                }
                m_pl.points.append(m_pl.point);
            }


            int r_l,g_l,b_l,a_l, r_b, g_b, b_b, a_b;
            obj_data[indx].my_pen.GetRGBA(r_l,g_l,b_l,a_l);
            obj_data[indx].my_pen.GetRGBA_brush(r_b,g_b,b_b,a_b);
            m_pl.pen.SetRGBA(r_l,g_l,b_l,a_l);
            m_pl.pen.SetWidth(obj_data[indx].my_pen.GetWidth());
            m_pl.pen.SetStyle(obj_data[indx].my_pen.GetStyle());

            m_pl.pen.SetRGBA_brush(r_b,g_b,b_b,a_b);
            m_pl.draw(ui->widget->im);
            update();

            for (int i = 0; i < obj_data[indx].kol; ++i) {
                delete[] points[i];
            }
            delete[] points;
        }
        else if(selectedType == "Полигон"){
            polygon m_pp; //мой полигон
            int *mas = obj_data[indx].mas;
            int **points = new int *[obj_data[indx].kol];
            int cols = 2;

            for(int i = 0; i < obj_data[indx].kol; ++i){
                points[i] = new int[cols];
            }
            for (int i = 0; i < obj_data[indx].kol; ++i) {
                for (int j = 0; j < cols; ++j) {
                    int index = i * cols + j;
                    points[i][j] = mas[index];
                }
            }
            for (int i = 0; i < obj_data[indx].kol; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if(j == 0){
                        m_pp.point.setX(points[i][j]);
                    }
                    else{
                        m_pp.point.setY(points[i][j]);
                    }
                }
                m_pp.points.append(m_pp.point);
            }


            int r_l,g_l,b_l,a_l, r_b, g_b, b_b, a_b;
            obj_data[indx].my_pen.GetRGBA(r_l,g_l,b_l,a_l);
            obj_data[indx].my_pen.GetRGBA_brush(r_b,g_b,b_b,a_b);
            m_pp.pen.SetRGBA(r_l,g_l,b_l,a_l);
            m_pp.pen.SetWidth(obj_data[indx].my_pen.GetWidth());
            m_pp.pen.SetStyle(obj_data[indx].my_pen.GetStyle());
            m_pp.pen.SetStyleBrush(obj_data[indx].my_pen.GetStyleBrush());

            m_pp.pen.SetRGBA_brush(r_b,g_b,b_b,a_b);
            m_pp.draw(ui->widget->im);
            update();

            for (int i = 0; i < obj_data[indx].kol; ++i) {
                delete[] points[i];
            }
            delete[] points;
        }
    }
}

void MainWindow::on_pushButton_clear_clicked() //кнопка отчистки виджета
{
    ui -> widget -> im.fill(0);
    ui -> widget -> update();
}

void MainWindow::on_tableWidget_cellChanged(int row, int column) //обработка ручного изменения таблицы
{
    bool is_correct;
    if(row % 2 != 0){
        ui -> tableWidget -> item(row, column) -> text().toInt(&is_correct);
        if (is_correct or ui -> tableWidget -> item(row, column) -> text() == "---")
        {
            ui -> tableWidget -> item(row, column) -> setBackground(Qt::white);
        }
        else
        {
            ui -> tableWidget -> item(row, column) -> setBackground(Qt::red);
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event) //обработчик закрытия формы
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "СуперРисовашка", "Вы действительно желаете выйти из программы? Не сохраненные изменения будут утеряны.", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
    if (reply == QMessageBox::Yes)
    {
        event -> accept(); //принимаем сигнал
    }
    else if (reply == QMessageBox::No)
    {
        event -> ignore(); //игнорируем сигнал
    }
}

void MainWindow::on_pushButton_Load_clicked() //загрузка значений
{
    QFile file;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть bin"), "C:/Users/student.A-424/Desktop", tr("Binary files(*.bin)"));
    if(fileName.isEmpty())
    {
        return;
    }
    else
    {
        QString f = QFileInfo(fileName).suffix();
        if(f != "bin")
        {
            QMessageBox::warning(this,"Хах","Так низзя");
            return;
        }

        file.setFileName(fileName);
        //        file.open(QIODevice::ReadOnly);
        //        qlonglong fileSize = file.size(); // определяем размер файла
        //        qint64 offset = fileSize - 64; // смещение до контрольной суммы
        //        file.seek(offset); // переводим в конец файла
        //        QByteArray hashData = file.read(64); // считываем контрольную сумму в бинарном формате
        //        qDebug() << hashData;
        //        QByteArray data = file.read(fileSize); // читаем все содержимое файла, кроме последних 64 байт
        //        QCryptographicHash hash(QCryptographicHash::Sha256);
        //        hash.addData(data); // применяем алгоритм хэширования к содержимому файла без последних 64 байт
        //        QByteArray fileHash = hash.result().toHex(); // получение результата хеширования в виде строки
        //        qDebug() << fileHash; // вывод полученного значения хеш-суммы
        //        if (hashData != fileHash) {
        //            QMessageBox::critical(nullptr, "Ошибка", "Файл был изменен. Я не буду это открывать. Вдруг там бяка :)");
        //            file.close();
        //            return;
        //        }
        //        file.close();
        file.open(QIODevice::ReadWrite);
        qlonglong fileSize = file.size(); // определяем размер файла
        qint64 offset = fileSize - 64; // смещение до контрольной суммы
        file.seek(offset); // переводим в конец файла
        QByteArray hashData = file.read(64); // считываем контрольную сумму в бинарном формате

        qint64 newPosition = fileSize-68;
        file.seek(newPosition); // установить позицию записи на 64 байта позади
        file.resize(newPosition);
        file.close();

        QFile file(fileName);
        if (file.open(QIODevice::ReadWrite)) {
            QByteArray data = file.readAll(); // читаем содержимое файла
            QCryptographicHash hash(QCryptographicHash::Sha256);
            hash.addData(data); // применяем алгоритм хэширования к содержимому файла
            fileHash = hash.result().toHex();

            if (hashData != fileHash) {
                QCryptographicHash hash(QCryptographicHash::Sha256);
                QDataStream out(&file);
                out << hashData;
                QMessageBox::critical(nullptr, "Ошибка", "Файл был изменен. Я не буду это открывать. Вдруг там бяка :)");
                file.close();
                return;
            }
        }
        file.close();

        file.setFileName(fileName);
        file.open(QIODevice::ReadOnly);
        char * mas = new char[sizeof (int)];

        ui -> tableWidget -> clear();
        ui -> spinBox -> setValue(0);

        int kol_elem;
        int val,val2,indx = 0;
        int row = 0;
        QComboBox * cb;

        on_spinBox_valueChanged(0);
        //первое значение количество примитивов
        file.read(mas,sizeof (int));
        memcpy(&kol_elem,mas,sizeof (int));

        ui->spinBox->setValue(kol_elem);

        while (!file.atEnd()||(indx > kol_elem))
        {
            row = indx + indx + 1;
            //фигура
            file.read(mas,sizeof (int));
            memcpy(&val,mas,sizeof (int));

            cb = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(row,0));

            cb->setCurrentIndex(val);

            switch (val)
            {
            case 0: //точка
            {
                //X
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,1)->setText(QString::number(val2));

                //Y
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,2)->setText(QString::number(val2));

                int a,r,g,b;
                //color
                file.read(mas,sizeof (int));
                memcpy(&r,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&g,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&b,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&a,mas,sizeof (int));
                obj_data[indx].my_pen.SetRGBA(r,g,b,a);

                //width
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetWidth(val2);

                break;
            }
            case 1: //линия
            {
                //X1
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,1)->setText(QString::number(val2));

                //Y1
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,2)->setText(QString::number(val2));

                //X2
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,3)->setText(QString::number(val2));

                //Y2
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,4)->setText(QString::number(val2));

                int a,r,g,b;
                //color
                file.read(mas,sizeof (int));
                memcpy(&r,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&g,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&b,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&a,mas,sizeof (int));
                obj_data[indx].my_pen.SetRGBA(r,g,b,a);

                //width
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetWidth(val2);

                //style
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetStyle(val2);
                break;

            }
            case 2: //прямоугольник
            {
                //X1
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,1)->setText(QString::number(val2));

                //Y1
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,2)->setText(QString::number(val2));

                //X2
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,3)->setText(QString::number(val2));

                //Y2
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,4)->setText(QString::number(val2));

                int a,r,g,b;
                //color
                file.read(mas,sizeof (int));
                memcpy(&r,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&g,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&b,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&a,mas,sizeof (int));
                obj_data[indx].my_pen.SetRGBA(r,g,b,a);

                //width
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetWidth(val2);

                //style
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetStyle(val2);

                //color brush
                file.read(mas,sizeof (int));
                memcpy(&r,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&g,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&b,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&a,mas,sizeof (int));
                obj_data[indx].my_pen.SetRGBA_brush(r,g,b,a);

                //style brush
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetStyleBrush(val2);

                break;
            }
            case 3: //окружность
            {
                //X
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,1)->setText(QString::number(val2));

                //Y
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,2)->setText(QString::number(val2));

                //R
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,3)->setText(QString::number(val2));

                int a,r,g,b;
                //color
                file.read(mas,sizeof (int));
                memcpy(&r,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&g,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&b,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&a,mas,sizeof (int));
                obj_data[indx].my_pen.SetRGBA(r,g,b,a);

                //width
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetWidth(val2);

                //style
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetStyle(val2);

                //color brush
                file.read(mas,sizeof (int));
                memcpy(&r,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&g,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&b,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&a,mas,sizeof (int));
                obj_data[indx].my_pen.SetRGBA_brush(r,g,b,a);

                //style brush
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetStyleBrush(val2);

                break;
            }
            case 4: //эллипс
            {
                //X
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,1)->setText(QString::number(val2));

                //Y
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,2)->setText(QString::number(val2));

                //Rx
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,3)->setText(QString::number(val2));

                //Ry
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,4)->setText(QString::number(val2));

                int a,r,g,b;
                //color
                file.read(mas,sizeof (int));
                memcpy(&r,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&g,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&b,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&a,mas,sizeof (int));
                obj_data[indx].my_pen.SetRGBA(r,g,b,a);

                //width
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetWidth(val2);

                //style
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetStyle(val2);

                //color brush
                file.read(mas,sizeof (int));
                memcpy(&r,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&g,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&b,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&a,mas,sizeof (int));
                obj_data[indx].my_pen.SetRGBA_brush(r,g,b,a);

                //style brush
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetStyleBrush(val2);

                break;
            }
            case 5: //треугольник
            {
                //X1
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,1)->setText(QString::number(val2));

                //Y1
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,2)->setText(QString::number(val2));

                //X2
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,3)->setText(QString::number(val2));

                //Y2
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,4)->setText(QString::number(val2));

                //X3
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,5)->setText(QString::number(val2));

                //Y3
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,6)->setText(QString::number(val2));

                int a,r,g,b;
                //color
                file.read(mas,sizeof (int));
                memcpy(&r,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&g,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&b,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&a,mas,sizeof (int));
                obj_data[indx].my_pen.SetRGBA(r,g,b,a);

                //width
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetWidth(val2);

                //style
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetStyle(val2);

                //color brush
                file.read(mas,sizeof (int));
                memcpy(&r,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&g,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&b,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&a,mas,sizeof (int));
                obj_data[indx].my_pen.SetRGBA_brush(r,g,b,a);

                //style brush
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetStyleBrush(val2);

                break;
            }
            case 6: //дуга
            {
                //X
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,1)->setText(QString::number(val2));

                //Y
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,2)->setText(QString::number(val2));

                //Rx
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,3)->setText(QString::number(val2));

                //Ry
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,4)->setText(QString::number(val2));

                //St
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,5)->setText(QString::number(val2));

                //Sp
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,6)->setText(QString::number(val2));

                int a,r,g,b;
                //color
                file.read(mas,sizeof (int));
                memcpy(&r,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&g,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&b,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&a,mas,sizeof (int));
                obj_data[indx].my_pen.SetRGBA(r,g,b,a);

                //width
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetWidth(val2);

                //style
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetStyle(val2);
                break;

            }
            case 7: //сегмент
            {
                //X
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,1)->setText(QString::number(val2));

                //Y
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,2)->setText(QString::number(val2));

                //Rx
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,3)->setText(QString::number(val2));

                //Ry
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,4)->setText(QString::number(val2));

                //St
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,5)->setText(QString::number(val2));

                //Sp
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,6)->setText(QString::number(val2));

                int a,r,g,b;
                //color
                file.read(mas,sizeof (int));
                memcpy(&r,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&g,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&b,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&a,mas,sizeof (int));
                obj_data[indx].my_pen.SetRGBA(r,g,b,a);

                //width
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetWidth(val2);

                //style
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetStyle(val2);

                //color brush
                file.read(mas,sizeof (int));
                memcpy(&r,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&g,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&b,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&a,mas,sizeof (int));
                obj_data[indx].my_pen.SetRGBA_brush(r,g,b,a);

                //style brush
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetStyleBrush(val2);
                break;

            }
            case 8: //сектор
            {
                //X
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,1)->setText(QString::number(val2));

                //Y
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,2)->setText(QString::number(val2));

                //Rx
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,3)->setText(QString::number(val2));

                //Ry
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,4)->setText(QString::number(val2));

                //St
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,5)->setText(QString::number(val2));

                //Sp
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                ui->tableWidget->item(row,6)->setText(QString::number(val2));

                int a,r,g,b;
                //color
                file.read(mas,sizeof (int));
                memcpy(&r,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&g,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&b,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&a,mas,sizeof (int));
                obj_data[indx].my_pen.SetRGBA(r,g,b,a);

                //width
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetWidth(val2);

                //style
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetStyle(val2);

                //color brush
                file.read(mas,sizeof (int));
                memcpy(&r,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&g,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&b,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&a,mas,sizeof (int));
                obj_data[indx].my_pen.SetRGBA_brush(r,g,b,a);

                //style brush
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetStyleBrush(val2);
                break;

            }
            case 9: //ломаная линия
            {
                //количество вершин
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                int kol2=val2+val2;
                obj_data[indx].kol = val2;
                obj_data[indx].mas=new int[kol2];
                for (int j=0;j<kol2;j++)
                {
                    file.read(mas,sizeof (int));
                    memcpy(&val2,mas,sizeof (int));
                    obj_data[indx].mas[j]=val2;
                    //memcpy(&obj_data[indx].mas[j],mas,sizeof (int));
                }

                int a,r,g,b;
                //color
                file.read(mas,sizeof (int));
                memcpy(&r,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&g,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&b,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&a,mas,sizeof (int));
                obj_data[indx].my_pen.SetRGBA(r,g,b,a);

                //width
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetWidth(val2);

                //style
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetStyle(val2);

                break;
            }
            case 10: //полигон
            {
                //количество вершин
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                int kol2=val2+val2;
                obj_data[indx].kol = val2;
                obj_data[indx].mas=new int[kol2];

                for (int j=0;j<kol2;j++)
                {
                    file.read(mas,sizeof (int));
                    memcpy(&val2,mas,sizeof (int));
                    obj_data[indx].mas[j]=val2;
                    //memcpy(&obj_data[indx].mas[j],mas,sizeof (int));
                }

                int a,r,g,b;
                //color
                file.read(mas,sizeof (int));
                memcpy(&r,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&g,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&b,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&a,mas,sizeof (int));
                obj_data[indx].my_pen.SetRGBA(r,g,b,a);

                //width
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetWidth(val2);

                //style
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetStyle(val2);

                //color brush
                file.read(mas,sizeof (int));
                memcpy(&r,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&g,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&b,mas,sizeof (int));
                file.read(mas,sizeof (int));
                memcpy(&a,mas,sizeof (int));
                obj_data[indx].my_pen.SetRGBA_brush(r,g,b,a);

                //style brush
                file.read(mas,sizeof (int));
                memcpy(&val2,mas,sizeof (int));
                obj_data[indx].my_pen.SetStyleBrush(val2);

                break;
            }
            default:
            {
                //ошибка или недописано что-то
                break;
            }
            }

            indx++;
        }
        file2 = fileName; //запомнили путь)

        //Вывод названия окна
        QFileInfo fileInfo(file.fileName());
        QString fileName(fileInfo.fileName());
        QWidget::setWindowTitle(fileName); //выводим название
        way = fileName; //запомнили имя

        file.close();
        delete [] mas;

        QFile file1(file2);
        if (file.open(QIODevice::ReadWrite)) {
            QByteArray data = file.readAll(); // читаем содержимое файла
            QCryptographicHash hash(QCryptographicHash::Sha256);
            hash.addData(data); // применяем алгоритм хэширования к содержимому файла
            QByteArray fileHash = hash.result().toHex();
            QDataStream out(&file);
            out << fileHash;
        }
        file.close();
        // QMessageBox::information(this,"Открытие","Я открыл)");
    }
    on_pushButton_clear_clicked();
}
void MainWindow::on_pushButton_Save_clicked() //сохранение значений таблицы
{
    if(ui -> spinBox -> value() == 0){
        QMessageBox::information(this,"Опасно","Таблица не создана");
        return;
    }

    correct_value = true;
    int row = ui -> tableWidget -> rowCount();
    for(int i = 0; i < row; ++i){
        for(int j = 0; j < 8; ++j){
            if(ui -> tableWidget -> item(i,j) != nullptr){
                QBrush brush = ui -> tableWidget -> item(i,j) -> background();
                if(brush.color() == Qt::red){
                    correct_value = false;
                    break;
                }
            }
            if(!correct_value)
                break;
        }
        if(!correct_value)
            break;
    }

    if(!correct_value){
        QMessageBox::information(this,"Ошибка!","Таблица должна содержать только числа");
        return;
    }

    QFile file;
    if(file2.isEmpty())
    {
        on_pushButton_Save_as_clicked();
    }
    else
    {
        char * mas = new char[sizeof (int)];
        file.setFileName(file2);
        file.open(QIODevice::WriteOnly);

        int kol_elem=ui->spinBox->value();
        int val,val2,indx;
        bool flag;
        int size_tabl=kol_elem*2;
        QComboBox * cb;
        //первое значение количество примитивов
        memcpy(mas,&kol_elem,sizeof (int));
        file.write(mas,sizeof (int));

        for (int i=1;i<size_tabl;i+=2)
        {
            //пишем индекс текущего примитива
            cb = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,0));
            val=cb->currentIndex();
            memcpy(mas,&val,sizeof (int));
            file.write(mas,sizeof (int));

            switch (val)
            {
            case 0: //точка
            {
                //X
                val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y
                val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                indx= (i-1)/2;
                int a,r,g,b;
                //color
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                break;
            }
            case 1: //линия
            {
                //X1
                val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y1
                val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //X2
                val2=ui->tableWidget->item(i,3)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y2
                val2=ui->tableWidget->item(i,4)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                indx = (i-1)/2;
                int a,r,g,b;
                //color
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                break;

            }
            case 2: //прямоугольник
            {
                //X1
                val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y1
                val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //X2
                val2=ui->tableWidget->item(i,3)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y2
                val2=ui->tableWidget->item(i,4)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                indx = (i-1)/2;
                int a,r,g,b;
                //color pen
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width pen
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style pen
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //color brush
                obj_data[indx].my_pen.GetRGBA_brush(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //style brush
                val2=obj_data[indx].my_pen.GetStyleBrush();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                break;
            }
            case 3: //окружность
            {
                //X
                val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y
                val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //R
                val2=ui->tableWidget->item(i,3)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                indx = (i-1)/2;
                int a,r,g,b;
                //color pen
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width pen
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style pen
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //color brush
                obj_data[indx].my_pen.GetRGBA_brush(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //style brush
                val2=obj_data[indx].my_pen.GetStyleBrush();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                break;
            }
            case 4: //эллипс
            {
                //X
                val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y
                val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Rx
                val2=ui->tableWidget->item(i,3)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Ry
                val2=ui->tableWidget->item(i,4)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                indx = (i-1)/2;
                int a,r,g,b;
                //color pen
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width pen
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style pen
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //color brush
                obj_data[indx].my_pen.GetRGBA_brush(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //style brush
                val2=obj_data[indx].my_pen.GetStyleBrush();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                break;
            }
            case 5: //треугольник
            {
                //X1
                val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y1
                val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //X2
                val2=ui->tableWidget->item(i,3)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y2
                val2=ui->tableWidget->item(i,4)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //X3
                val2=ui->tableWidget->item(i,5)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y3
                val2=ui->tableWidget->item(i,6)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                indx = (i-1)/2;
                int a,r,g,b;
                //color pen
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width pen
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style pen
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //color brush
                obj_data[indx].my_pen.GetRGBA_brush(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //style brush
                val2=obj_data[indx].my_pen.GetStyleBrush();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                break;
            }
            case 6: //дуга
            {
                //X
                val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y
                val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Rx
                val2=ui->tableWidget->item(i,3)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Ry
                val2=ui->tableWidget->item(i,4)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //St
                val2=ui->tableWidget->item(i,5)->text().toInt(&flag);
                if (!flag or val2 < -360 or val2 > 360)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Sp
                val2=ui->tableWidget->item(i,6)->text().toInt(&flag);
                if (!flag or val2 < -360 or val2 > 360)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                indx = (i-1)/2;
                int a,r,g,b;
                //color
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                break;

            }
            case 7: //сегмент
            {
                //X
                val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y
                val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Rx
                val2=ui->tableWidget->item(i,3)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Ry
                val2=ui->tableWidget->item(i,4)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //St
                val2=ui->tableWidget->item(i,5)->text().toInt(&flag);
                if (!flag or val2 > 360 or val2 < -360)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Sp
                val2=ui->tableWidget->item(i,6)->text().toInt(&flag);
                if (!flag or val2 > 360 or val2 < -360)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                indx = (i-1)/2;
                int a,r,g,b;
                //color pen
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width pen
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style pen
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //color brush
                obj_data[indx].my_pen.GetRGBA_brush(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //style brush
                val2=obj_data[indx].my_pen.GetStyleBrush();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                break;

            }
            case 8: //сектор
            {
                //X
                val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y
                val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Rx
                val2=ui->tableWidget->item(i,3)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Ry
                val2=ui->tableWidget->item(i,4)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //St
                val2=ui->tableWidget->item(i,5)->text().toInt(&flag);
                if (!flag or val2 > 360 or val2 < -360)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Sp
                val2=ui->tableWidget->item(i,6)->text().toInt(&flag);
                if (!flag or val2 > 360 or val2 < -360)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                indx = (i-1)/2;
                int a,r,g,b;
                //color pen
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width pen
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style pen
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //color brush
                obj_data[indx].my_pen.GetRGBA_brush(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //style brush
                val2=obj_data[indx].my_pen.GetStyleBrush();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                break;

            }
            case 9: //ломаная линия
            {
                indx= (i-1)/2;
                //количество вершин
                val2=obj_data[indx].kol;
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                int kol2=val2+val2;
                for (int j=0;j<kol2;j++)
                {
                    val2=obj_data[indx].mas[j];
                    memcpy(mas,&val2,sizeof (int));
                    //memcpy(mas,&obj_data[indx].mas[j],sizeof (int));
                    file.write(mas,sizeof (int));
                }

                int a,r,g,b;
                //color
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                break;
            }
            case 10: //полигон
            {
                indx= (i-1)/2;
                //количество вершин
                val2=obj_data[indx].kol;
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                int kol2=val2+val2;
                for (int j=0;j<kol2;j++)
                {
                    val2=obj_data[indx].mas[j];
                    memcpy(mas,&val2,sizeof (int));
                    //memcpy(mas,&obj_data[indx].mas[j],sizeof (int));
                    file.write(mas,sizeof (int));
                }

                int a,r,g,b;
                //color
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //color brush
                obj_data[indx].my_pen.GetRGBA_brush(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //style brush
                val2=obj_data[indx].my_pen.GetStyleBrush();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                break;
            }

            default:
            {
                //ошибка или недописано что-то
                break;
            }
            }
        }

        QWidget::setWindowTitle(way); //*//

        file.close();
        delete [] mas;
        QFile file(file2);
        if (file.open(QIODevice::ReadWrite)) {
            QByteArray data = file.readAll(); // читаем содержимое файла
            QCryptographicHash hash(QCryptographicHash::Sha256);
            hash.addData(data); // применяем алгоритм хэширования к содержимому файла
            QByteArray fileHash = hash.result().toHex();
            QDataStream out(&file);
            out << fileHash;
        }
        file.close();
        QMessageBox::information(this,"Сохранение","Файл успешно сохранен.");

    }
}
void MainWindow::on_pushButton_Save_as_clicked()//кнопка сохранить как
{
    if(ui -> spinBox -> value() == 0){
        QMessageBox::information(this,"Опасно","Таблица не создана");
        return;
    }

    correct_value = true;
    int row = ui -> tableWidget -> rowCount();
    for(int i = 0; i < row; ++i){
        for(int j = 0; j < 8; ++j){
            if(ui -> tableWidget -> item(i,j) != nullptr){
                QBrush brush = ui -> tableWidget -> item(i,j) -> background();
                if(brush.color() == Qt::red){
                    correct_value = false;
                    break;
                }
            }
            if(!correct_value)
                break;
        }
        if(!correct_value)
            break;
    }

    if(!correct_value){
        QMessageBox::information(this,"Ошибка!","Таблица должна содержать только числа");
        return;
    }
    QString fileName;
    QFile file;
    fileName = QFileDialog::getSaveFileName(this, tr("Сохранить как bin"), "C:/Users/student.A-424/Desktop", tr("Binary files(*.bin)"));
    if(fileName.isEmpty())
    {
        return;
    }
    QString f = QFileInfo(fileName).suffix();
    if(f != "bin")
    {
        QMessageBox::warning(this,"Хах","Так низзя");
        return;
    }
    else
    {
        char * mas = new char[sizeof (int)];
        file.setFileName(fileName);
        file.open(QIODevice::WriteOnly);

        int kol_elem=ui->spinBox->value();
        int val,val2,indx;
        bool flag;
        int size_tabl=kol_elem*2;
        QComboBox * cb;
        //первое значение количество примитивов
        memcpy(mas,&kol_elem,sizeof (int));
        file.write(mas,sizeof (int));

        for (int i=1;i<size_tabl;i+=2)
        {
            //пишем индекс текущего примитива
            cb = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,0));
            val=cb->currentIndex();
            memcpy(mas,&val,sizeof (int));
            file.write(mas,sizeof (int));

            switch (val)
            {
            case 0: //точка
            {
                //X
                val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y
                val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                indx= (i-1)/2;
                int a,r,g,b;
                //color
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                break;
            }
            case 1: //линия
            {
                //X1
                val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y1
                val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //X2
                val2=ui->tableWidget->item(i,3)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y2
                val2=ui->tableWidget->item(i,4)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                indx = (i-1)/2;
                int a,r,g,b;
                //color
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                break;

            }
            case 2: //прямоугольник
            {
                //X1
                val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y1
                val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //X2
                val2=ui->tableWidget->item(i,3)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y2
                val2=ui->tableWidget->item(i,4)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                indx = (i-1)/2;
                int a,r,g,b;
                //color pen
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width pen
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style pen
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //color brush
                obj_data[indx].my_pen.GetRGBA_brush(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //style brush
                val2=obj_data[indx].my_pen.GetStyleBrush();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                break;
            }
            case 3: //окружность
            {
                //X
                val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y
                val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //R
                val2=ui->tableWidget->item(i,3)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                indx = (i-1)/2;
                int a,r,g,b;
                //color pen
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width pen
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style pen
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //color brush
                obj_data[indx].my_pen.GetRGBA_brush(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //style brush
                val2=obj_data[indx].my_pen.GetStyleBrush();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                break;
            }
            case 4: //эллипс
            {
                //X
                val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y
                val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Rx
                val2=ui->tableWidget->item(i,3)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Ry
                val2=ui->tableWidget->item(i,4)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                indx = (i-1)/2;
                int a,r,g,b;
                //color pen
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width pen
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style pen
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //color brush
                obj_data[indx].my_pen.GetRGBA_brush(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //style brush
                val2=obj_data[indx].my_pen.GetStyleBrush();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                break;
            }
            case 5: //треугольник
            {
                //X1
                val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y1
                val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //X2
                val2=ui->tableWidget->item(i,3)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y2
                val2=ui->tableWidget->item(i,4)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //X3
                val2=ui->tableWidget->item(i,5)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y3
                val2=ui->tableWidget->item(i,6)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                indx = (i-1)/2;
                int a,r,g,b;
                //color pen
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width pen
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style pen
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //color brush
                obj_data[indx].my_pen.GetRGBA_brush(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //style brush
                val2=obj_data[indx].my_pen.GetStyleBrush();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                break;
            }
            case 6: //дуга
            {
                //X
                val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y
                val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Rx
                val2=ui->tableWidget->item(i,3)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Ry
                val2=ui->tableWidget->item(i,4)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //St
                val2=ui->tableWidget->item(i,5)->text().toInt(&flag);
                if (!flag or val2 < -360 or val2 > 360)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Sp
                val2=ui->tableWidget->item(i,6)->text().toInt(&flag);
                if (!flag or val2 < -360 or val2 > 360)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                indx = (i-1)/2;
                int a,r,g,b;
                //color
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                break;

            }
            case 7: //сегмент
            {
                //X
                val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y
                val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Rx
                val2=ui->tableWidget->item(i,3)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Ry
                val2=ui->tableWidget->item(i,4)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //St
                val2=ui->tableWidget->item(i,5)->text().toInt(&flag);
                if (!flag or val2 > 360 or val2 < -360)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Sp
                val2=ui->tableWidget->item(i,6)->text().toInt(&flag);
                if (!flag or val2 > 360 or val2 < -360)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                indx = (i-1)/2;
                int a,r,g,b;
                //color pen
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width pen
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style pen
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //color brush
                obj_data[indx].my_pen.GetRGBA_brush(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //style brush
                val2=obj_data[indx].my_pen.GetStyleBrush();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                break;

            }
            case 8: //сектор
            {
                //X
                val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Y
                val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Rx
                val2=ui->tableWidget->item(i,3)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Ry
                val2=ui->tableWidget->item(i,4)->text().toInt(&flag);
                if (!flag or val2 > 32000 or val2 < -32000)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //St
                val2=ui->tableWidget->item(i,5)->text().toInt(&flag);
                if (!flag or val2 > 360 or val2 < -360)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                //Sp
                val2=ui->tableWidget->item(i,6)->text().toInt(&flag);
                if (!flag or val2 > 360 or val2 < -360)
                {
                    QMessageBox::information(this,"Ошибка","Проверьте значения координат");
                    delete [] mas;
                    file.close();
                    file.remove();
                    return;
                }
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                indx = (i-1)/2;
                int a,r,g,b;
                //color pen
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width pen
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style pen
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //color brush
                obj_data[indx].my_pen.GetRGBA_brush(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //style brush
                val2=obj_data[indx].my_pen.GetStyleBrush();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                break;

            }
            case 9: //ломаная линия
            {
                indx= (i-1)/2;
                //количество вершин
                val2=obj_data[indx].kol;
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                int kol2=val2+val2;
                for (int j=0;j<kol2;j++)
                {
                    val2=obj_data[indx].mas[j];
                    memcpy(mas,&val2,sizeof (int));
                    //memcpy(mas,&obj_data[indx].mas[j],sizeof (int));
                    file.write(mas,sizeof (int));
                }

                int a,r,g,b;
                //color
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                break;
            }
            case 10: //полигон
            {
                indx= (i-1)/2;
                //количество вершин
                val2=obj_data[indx].kol;
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                int kol2=val2+val2;
                for (int j=0;j<kol2;j++)
                {
                    val2=obj_data[indx].mas[j];
                    memcpy(mas,&val2,sizeof (int));
                    //memcpy(mas,&obj_data[indx].mas[j],sizeof (int));
                    file.write(mas,sizeof (int));
                }

                int a,r,g,b;
                //color
                obj_data[indx].my_pen.GetRGBA(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //width
                val2=obj_data[indx].my_pen.GetWidth();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //style
                val2=obj_data[indx].my_pen.GetStyle();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));
                //color brush
                obj_data[indx].my_pen.GetRGBA_brush(r,g,b,a);
                memcpy(mas,&r,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&g,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&b,sizeof (int));
                file.write(mas,sizeof (int));
                memcpy(mas,&a,sizeof (int));
                file.write(mas,sizeof (int));
                //style brush
                val2=obj_data[indx].my_pen.GetStyleBrush();
                memcpy(mas,&val2,sizeof (int));
                file.write(mas,sizeof (int));

                break;
            }

            default:
            {
                //ошибка или недописано что-то
                break;
            }
            }
        }

        file2 = fileName;
        //Вывод названия окна
        QFileInfo fileInfo(file.fileName());
        QString fileName(fileInfo.fileName());
        QWidget::setWindowTitle(fileName); //выводим название
        way = fileName; //запомнили имя


        file.close();
        delete [] mas;

        QFile file(file2);
        if (file.open(QIODevice::ReadWrite)) {
            QByteArray data = file.readAll(); // читаем содержимое файла
            QCryptographicHash hash(QCryptographicHash::Sha256);
            hash.addData(data); // применяем алгоритм хэширования к содержимому файла
            QByteArray fileHash = hash.result().toHex();
            QDataStream out(&file);
            out << fileHash;
        }
        file.close();
        QMessageBox::information(this,"Сохранение","Файл успешно сохранен.");
    }
}

void MainWindow::on_pushButton_SaveWidget_clicked() //сохранить как картинку
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Сохранить изображение"), "C:/Users/student.A-424/Desktop", tr("Images (*.png *jpg)"));

    if (filePath.isEmpty())
    {
        return;
    }
    QString f = QFileInfo(filePath).suffix();
    if(f != "png" and f != "jpg")
    {
        QMessageBox::warning(this,"Хах","Так низзя");
        return;
    }

    QPixmap pixmap(ui ->widget->size());
    ui -> widget->render(&pixmap);
    QImage image = pixmap.toImage();
    image.save(filePath, "png");
}
