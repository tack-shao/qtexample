#include "calendarwidget.h"
#include "date.h"
#include "database.h"

#include <QInputDialog>
#include <QPainter>
#include <QStyleOption>
#include <QDateTime>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QLabel>
#include <QDate>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QDebug>
#include <QFont>

static const QString s_strWeek[] = {
    QObject::tr("周日"), QObject::tr("周一"), QObject::tr("周二"),
    QObject::tr("周三"), QObject::tr("周四"), QObject::tr("周五"),
    QObject::tr("周六"),
};

CalendarWidget::CalendarWidget(QWidget *parent)
    : QWidget(parent), m_nMonth(1)
{
    // 获取当前年月日
    m_nYear  = QDate::currentDate().year();
    m_nMonth = QDate::currentDate().month();
    m_nDay = QDate::currentDate().day();

    initWidget();
    initDate();
}

CalendarWidget::~CalendarWidget()
{

}

int CalendarWidget::year() const
{
    return m_nYear;
}

void CalendarWidget::setYear(int nYear)
{
    m_nYear = nYear;
}

int CalendarWidget::month() const
{
    return m_nMonth;
}

void CalendarWidget::setMonth(int nMonth)
{
    m_nMonth = nMonth;
}

int CalendarWidget::day() const
{
    return m_nDay;
}

void CalendarWidget::setDay(int nDay)
{
    m_nDay = nDay;
}

void CalendarWidget::jumpTodate(int year, int month, int day)
{
    setYear(year);
    setMonth(month);
    setDay(day);

    initDate();
}

/**
 * @brief CalendarWidget::initWidget 初始化界面
 */
void CalendarWidget::initWidget()
{
#ifdef Q_OS_ANDROID
    this->setMinimumSize(1400, 800);
#else
    this->setMinimumSize(427, 350);
    this->setObjectName("widgetCalendar");
#endif

    verLayoutCalendar = new QVBoxLayout(this);
    verLayoutCalendar->setContentsMargins(2, 2, 2, 2);
    verLayoutCalendar->setSpacing(0);

    //! [2]
    widgetTitle = new QWidget(this);
    widgetTitle->setObjectName("widgetTitle");

#ifdef Q_OS_ANDROID
    widgetTitle->setFixedHeight(80);
#else
    widgetTitle->setMinimumHeight(20);
#endif

    btnPrevMonth = new QPushButton(widgetTitle);
    btnPrevMonth->setText(tr("上月"));

    labelTitle = new QLabel(widgetTitle);
    labelTitle->setAlignment(Qt::AlignCenter);
    labelTitle->setObjectName("labelTitle");
    labelTitle->setText(tr("2016 年 04 月"));

    btnNextMonth = new QPushButton(widgetTitle);
    btnNextMonth->setText(tr("下月"));

    horLayoutTitle = new QHBoxLayout(widgetTitle);
    horLayoutTitle->addWidget(btnPrevMonth);
    horLayoutTitle->addWidget(labelTitle, 1);
    horLayoutTitle->addWidget(btnNextMonth);

    verLayoutCalendar->addWidget(widgetTitle);

    connect(btnPrevMonth, SIGNAL(clicked(bool)), this, SLOT(sltShowPrevMonth()));
    connect(btnNextMonth, SIGNAL(clicked(bool)), this, SLOT(sltShowNextMonth()));
    //! [2]

    //! [3]
    widgetWeek = new QWidget(this);
    widgetWeek->setObjectName("widgetWeek");

    horLayoutWeek = new QHBoxLayout(widgetWeek);
    horLayoutWeek->setContentsMargins(0, 0, 0, 0);
    horLayoutWeek->setSpacing(0);

    for (int i = 0; i < Week; i++) {
        labelWeek[i] = new QLabel(widgetWeek);
        labelWeek[i]->setText(s_strWeek[i]);
        labelWeek[i]->setObjectName("labelWeek");
        labelWeek[i]->setMinimumHeight(30);
        labelWeek[i]->setAlignment(Qt::AlignCenter);
        if ((0 == (i % 7)) || (6 == (i% 7))) {
            labelWeek[i]->setProperty("weekend", true);
        }
        horLayoutWeek->addWidget(labelWeek[i]);
    }

    verLayoutCalendar->addWidget(widgetWeek);
    //! [3]

    //! [4]
    widgetBody = new QWidget(this);
    verLayoutCalendar->addWidget(widgetBody, 1);

    gridLayoutBody = new QGridLayout(widgetBody);
    gridLayoutBody->setHorizontalSpacing(0);
    gridLayoutBody->setVerticalSpacing(0);
    gridLayoutBody->setContentsMargins(0, 0, 0, 0);

    for (int i = 0; i < 42; i++) {
        labelDay[i] = new DayLabel(widgetBody);
        labelDay[i]->setObjectName("labelDay");
        labelDay[i]->setAlignment(Qt::AlignCenter);
        labelDay[i]->setText(QString::number(i));
        if ((0 == (i % 7)) || (6 == (i% 7))) {
            labelDay[i]->setProperty("weekend", true);
        }
        gridLayoutBody->addWidget(labelDay[i], i / 7, i % 7);
        connect(labelDay[i], SIGNAL(signalClicked(int,int)), this, SLOT(sltDayClicked(int,int)));
        connect(labelDay[i], SIGNAL(signalPlan(QString)), this, SIGNAL(signalPlan(QString)));
    }

    labelDay[10]->setSelected(true);
    //! [4]
}

/**
 * @brief CalendarWidget::initDate 初始化日期
 */
void CalendarWidget::initDate()
{
    // 首先判断当前月的第一天是星期几
    int nWeek  = Date::getFirstDayOfWeek(m_nYear, m_nMonth);
    int nMonthDays = Date::getMonthDays(m_nYear, m_nMonth);
    // 上月天数
    int nPreMonDays = Date::getMonthDays(1 == m_nMonth ? m_nYear - 1 : m_nYear, 1 == m_nMonth ? 12 : m_nMonth - 1);

    // 显示当前年月
    labelTitle->setText(tr("%1 年 %2 月")
                        .arg(m_nYear, 2, 10, QChar('0'))
                        .arg(m_nMonth, 2, 10, QChar('0')));

    // 显示上月剩余天数
    if (0 == nWeek) {
        // 显示上月天数
        for (int i = 0; i < 7; i++) {
            labelDay[i]->showDay((nPreMonDays - 7 + i + 1), "");
            labelDay[i]->setColor(PREV_MONTH_DAY);
        }
        // 显示下月天数
        for (int i = 0; i < (42 - nMonthDays - 7); i++) {
            labelDay[nMonthDays + 7 + i]->showDay((i + 1), "");
            labelDay[nMonthDays + 7 + i]->setColor(NEXT_MONTH_DAY);
        }
    }
    else {
        for (int i = 0; i < nWeek; i++) {
            labelDay[i]->showDay((nPreMonDays - nWeek + i + 1), "");
            labelDay[i]->setColor(PREV_MONTH_DAY);
        }

        // 显示下月天数
        for (int i = (nWeek + nMonthDays); i < 42; i++) {
            labelDay[i]->showDay((i - (nWeek + nMonthDays) + 1), "");
            labelDay[i]->setColor(NEXT_MONTH_DAY);
        }
    }

    // 显示当前月
    int nProperty = 1;
    QStringList strPlan;
    int index = 0;
    for (int i = nWeek; i < (nMonthDays + nWeek); i++) {
        index = 0 == nWeek ? (i + 7) : i;
        labelDay[index]->showDay(i - nWeek + 1, Date::getLunarDate(m_nYear, m_nMonth, i - nWeek + 1));
        nProperty = ((0 == (i % 7)) || (6 == (i% 7))) ? WEEKEND_DAY : CURR_MONTH_DAY;
        labelDay[index]->setColor(nProperty);
        // 显示计划
        strPlan = DataBase::selectDb(
                    QString("%1-%2-%3")
                    .arg(m_nYear, 4, 10,  QChar('0'))
                    .arg(m_nMonth, 2, 10, QChar('0'))
                    .arg(i - nWeek + 1, 2, 10,   QChar('0')));

        // 显示计划
        labelDay[index]->setPlan(strPlan);
    }

    // 显示当前天数
    labelDay[m_nDay + nWeek - 1]->setColor(CURRENT_DAY);
    // 发送更新信号
    Q_EMIT signalDayChanged();
}

/**
 * @brief CalendarWidget::sltDayClicked 点击响应
 * @param type  类型 0 表示上月 1表示下月
 * @param day  当前点击的天数
 */
void CalendarWidget::sltDayClicked(int type, int day)
{
    // 上月
    if (PREV_MONTH_DAY == type) {
        sltShowPrevMonth();
    }
    // 下月
    else if (NEXT_MONTH_DAY == type) {
        sltShowNextMonth();
    }
    // 当天/周末/当月天数都显示在右边，并转换成农历
    else if ((CURR_MONTH_DAY == type)
             || (WEEKEND_DAY == type)
             || (CURRENT_DAY == type)) {
        // 选中当天
        Q_EMIT signalDayClicked(day);
    }
}

/**
 * @brief CalendarWidget::sltShowPrevMonth 显示上月日期
 */
void CalendarWidget::sltShowPrevMonth()
{
    m_nMonth--;
    if (m_nMonth < 1) {
        m_nMonth = 12;
        m_nYear--;
    }

    initDate();
}

/**
 * @brief CalendarWidget::sltShowNextMonth 显示下月日期
 */
void CalendarWidget::sltShowNextMonth()
{
    m_nMonth++;
    if (m_nMonth > 12) {
        m_nMonth = 1;
        m_nYear++;
    }
    initDate();
}

//////////////////////////////////////
/// \brief DayLabel::DayLabel
/// \param parent
////////////////////////////////

#include <QMouseEvent>
#include <QEvent>
#include <QPixmap>
#include "event.h"

DayLabel::DayLabel(QWidget *parent):
    QLabel(parent)
{
    bSelect = false;
    m_nDay = 0;
    m_strListPlan.clear();

    labelIcon = new QLabel(this);
    labelIcon->setFixedSize(QSize(12, 12));
    labelIcon->setPixmap(QPixmap(":/images/eventindicator.png"));
    labelIcon->move(0, 0);
    labelIcon->setVisible(false);
}

bool DayLabel::getBSelect() const
{
    return bSelect;
}

void DayLabel::setSelected(bool value)
{
    bSelect = value;
    this->setStyleSheet(QString("background: #ffffff; border: 1px solid red; border-radius: 2px"));
}

void DayLabel::setColor(const int &type)
{
    // 设置控件属性类型
    this->setProperty("type", type);
    this->setSelected(CURRENT_DAY == type);

    // 其他月
    if ((PREV_MONTH_DAY == type) || (NEXT_MONTH_DAY == type)) {
        this->setStyleSheet("background: #ffffff; border-top: 1px solid #c3c3c3; border-left: 1px solid #c3c3c3; color: #999999;");
        labelIcon->setVisible(false);
    }
    // 当前月
    else if (CURR_MONTH_DAY == type) {
        this->setStyleSheet("background: #ffffff; border-top: 1px solid #c3c3c3; border-left: 1px solid #c3c3c3; color: #000000;");
    }
    // 周末
    else if (WEEKEND_DAY == type) {
        labelIcon->setVisible(false);
        this->setStyleSheet("background: #ffffff; border-top: 1px solid #c3c3c3; border-left: 1px solid #c3c3c3; color: #ff0000;");
    }
}

/**
 * @brief DayLabel::showDay
 * @param nDay
 * @param strLunar
 * @param type
 */
void DayLabel::showDay(int nDay, QString strLunar)
{
    QString strText = QString::number(nDay);
    this->m_nDay = nDay;

    if ("" != strLunar) {
        strText.append("\n");
        strText.append(strLunar);
    }

    this->setText(strText);
}

/**
 * @brief DayLabel::setPlan 设置计划和日程
 * @param plan
 */
void DayLabel::setPlan(QStringList plan)
{
    if (!plan.isEmpty()) {
        m_strListPlan = plan;
        this->setToolTip(m_strListPlan.at(1));
    }
    else {
        m_strListPlan.clear();
    }

    labelIcon->setVisible(!plan.isEmpty());
}

void DayLabel::enterEvent(QEvent *e)
{
    int nProperty = this->property("type").toInt();
    if (PREV_MONTH_DAY == nProperty || NEXT_MONTH_DAY == nProperty) return;

    this->setStyleSheet("background: #c8b9a6; border-top: 1px solid #c3c3c3; border-left: 1px solid #c3c3c3;");
    QLabel::enterEvent(e);
}

void DayLabel::leaveEvent(QEvent *e)
{
    int nProperty = this->property("type").toInt();
    if (PREV_MONTH_DAY == nProperty || NEXT_MONTH_DAY == nProperty) return;

    if (bSelect) {
        this->setStyleSheet("background: #ffffff; border: 1px solid red;");
    }
    else {
        this->setStyleSheet("background: #ffffff; border-top: 1px solid #c3c3c3; border-left: 1px solid #c3c3c3;");
    }
    QLabel::leaveEvent(e);
}

void DayLabel::mousePressEvent(QMouseEvent *e)
{
//    qDebug() << this->text() << this->property("type").toInt();
    Q_EMIT signalClicked(this->property("type").toInt(), m_nDay);
    if (!m_strListPlan.isEmpty()) {
        Q_EMIT signalPlan(m_strListPlan.at(1));
    }
    else {
         Q_EMIT signalPlan(tr("没有日程安排"));
    }
    QLabel::mousePressEvent(e);
}

void DayLabel::mouseDoubleClickEvent(QMouseEvent *e)
{
    //    qDebug() << "double";
    int nProperty = this->property("type").toInt();
    if (PREV_MONTH_DAY == nProperty || NEXT_MONTH_DAY == nProperty) return;

    bool ok;
    QString strText = "";
    if (!m_strListPlan.isEmpty()) {
        strText = m_strListPlan.at(1);
    }

    strText = QInputDialog::getText(this, tr("修改日程"),
                                         tr("您的出行计划"), QLineEdit::Normal,
                                         strText, &ok);
    if (ok && !strText.isEmpty())
        qDebug() << strText;
    QLabel::mouseDoubleClickEvent(e);
}

//////////////////////////////////////////
/// \brief Window::Window
/// \param parent
/////////////////////////////////////////

#include <QMessageBox>
#include "database.h"

Window::Window(QWidget *parent) :
    QWidget(parent)
{
    // 初始化数据库
    DataBase::connectdb();

    initWidget();
    initStyle();
    initDatabase();
}

Window::~Window()
{
}

void Window::initWidget()
{
    //! [1]
    calendar = new CalendarWidget(this);
    //! [1]

    //! [2]
    widgetRight     = new QWidget(this);
    widgetRight->setObjectName("widgetRight");
//    widgetRight->setMinimumSize(160, 350);

    labelShowToday       = new QLabel(widgetRight);
    labelShowWeek        = new QLabel(widgetRight);
    labelShowDay         = new QLabel(widgetRight);
    labelShowNYear       = new QLabel(widgetRight);
    labelShowLunarDate   = new QLabel(widgetRight);
    labelSpacer          = new QLabel(widgetRight);
    labelPlanTitle   = new QLabel(widgetRight);
    labelShowPlan        = new QLabel(widgetRight);

    labelShowToday->setAlignment(Qt::AlignCenter);
    labelShowWeek->setAlignment(Qt::AlignCenter);
    labelShowDay->setAlignment(Qt::AlignCenter);
    labelShowNYear->setAlignment(Qt::AlignCenter);
    labelShowLunarDate->setAlignment(Qt::AlignCenter);
    labelSpacer->setFixedSize(widgetRight->width(), 2);

    labelShowToday->setObjectName("labelCommon");
    labelShowWeek->setObjectName("labelCommon");
    labelShowDay->setObjectName("labelShowDay");
    labelShowNYear->setObjectName("labelCommon");
    labelShowLunarDate->setObjectName("labelCommon");
    labelSpacer->setObjectName("labelSpacer");
    labelPlanTitle->setObjectName("labelCommon");
    labelShowPlan->setObjectName("labelSchedule");

    labelShowToday->setText(QDateTime::currentDateTime().toString("yyyy 年 MM 月 dd日"));
    labelShowWeek->setText(QDate::currentDate().toString("ddd"));
    labelShowDay->setText(QDate::currentDate().toString("dd"));
    labelShowNYear->setText(tr("丙申猴年 壬辰月 甲子日"));
    labelShowLunarDate->setText(tr("农历 三月初六"));
    labelPlanTitle->setText(tr("今日行程安排"));
    labelShowPlan->setText(tr("今天需要完成数据采集工作！"));
    labelShowPlan->setWordWrap(true);

    verlayoutWidgetRight = new QVBoxLayout(widgetRight);
    verlayoutWidgetRight->setContentsMargins(0, 0, 0, 0);
    verlayoutWidgetRight->setSpacing(15);
    verlayoutWidgetRight->addWidget(labelShowToday);
    verlayoutWidgetRight->addWidget(labelShowWeek);
    verlayoutWidgetRight->addWidget(labelShowDay);
    verlayoutWidgetRight->addWidget(labelShowNYear);
    verlayoutWidgetRight->addWidget(labelShowLunarDate);
    verlayoutWidgetRight->addWidget(labelSpacer, 0, Qt::AlignCenter);
    verlayoutWidgetRight->addStretch(1);
    verlayoutWidgetRight->addWidget(labelPlanTitle);
    verlayoutWidgetRight->addWidget(labelShowPlan, 1);
    //! [2]

    horLayoutWidget = new QHBoxLayout();
    horLayoutWidget->addWidget(calendar, 3, Qt::AlignCenter);
    horLayoutWidget->addWidget(widgetRight, 1);

    //! [3]
    groupBoxBottom = new QGroupBox(this);

    labelYearJump = new QLabel(groupBoxBottom);
    labelMonthJump = new QLabel(groupBoxBottom);
    labelDayJump = new QLabel(groupBoxBottom);

    labelYearJump->setMinimumWidth(20);
    labelMonthJump->setMinimumWidth(20);
    labelDayJump->setMinimumWidth(20);

    labelYearJump->setObjectName("labelCommon");
    labelMonthJump->setObjectName("labelCommon");
    labelDayJump->setObjectName("labelCommon");

    labelYearJump->setText(tr("年:"));
    labelMonthJump->setText(tr("月:"));
    labelDayJump->setText(tr("日:"));
    ///////////////////////////////////

    editYearJump = new QLineEdit(groupBoxBottom);
    editMonthJump = new QLineEdit(groupBoxBottom);
    editDayJump = new QLineEdit(groupBoxBottom);

    editYearJump->setMaximumWidth(60);
    editMonthJump->setMaximumWidth(60);
    editDayJump->setMaximumWidth(60);

    editYearJump->setText("2016");
    editMonthJump->setText("1");
    editDayJump->setText("1");
    //////////////////////////////////

    btnDateJump = new QPushButton(groupBoxBottom);
    btnDateJump->setText(tr("跳转至该日期"));

    btnToday = new QPushButton(groupBoxBottom);
    btnToday->setText(tr("返回今天"));

    horLayoutJump = new QHBoxLayout(groupBoxBottom);
    horLayoutJump->setSpacing(10);
    horLayoutJump->addWidget(labelYearJump);
    horLayoutJump->addWidget(editYearJump);

    horLayoutJump->addWidget(labelMonthJump);
    horLayoutJump->addWidget(editMonthJump);

    horLayoutJump->addWidget(labelDayJump);
    horLayoutJump->addWidget(editDayJump);

    horLayoutJump->addStretch(1);
    horLayoutJump->addWidget(btnDateJump);
    horLayoutJump->addWidget(btnToday);

    //! [3]

    //! [4]
    verLayoutAll = new QVBoxLayout(this);
    verLayoutAll->setContentsMargins(10, 10, 10, 10);
    verLayoutAll->setSpacing(10);
    verLayoutAll->addLayout(horLayoutWidget, 1);
    verLayoutAll->addWidget(groupBoxBottom, 0);

    //! [4]
    connect(calendar, SIGNAL(signalDayChanged()), this, SLOT(sltDayChanged()));
    connect(calendar, SIGNAL(signalDayClicked(int)), this, SLOT(sltDayClicked(int)));
    connect(calendar, SIGNAL(signalPlan(QString)), this, SLOT(sltShowPlans(QString)));
    connect(btnDateJump, SIGNAL(clicked(bool)), this, SLOT(sltDateJump()));
    connect(btnToday, SIGNAL(clicked(bool)), this, SLOT(sltBack2today()));
}

void Window::initDatabase()
{
}


/**
 * @brief CalendarWidget::initStyle 初始化样式
 */
void Window::initStyle()
{
    QString strStyle = "";
#ifdef Q_OS_ANDROID
    strStyle += QString(".CalendarWidget {border: 1px solid #ff00ff;}");
    strStyle += QString(".Window {background: black;}");
    strStyle += QString(".DayLabel{font-size: 64px;}");
    strStyle += QString("QWidget#widgetRight{background-color: transparent;}");
    strStyle += QString("QWidget#widgetCalendar{ background-color: white;}");
    strStyle += QString("QWidget#widgetTitle{ background-color: #c8b9a6;}");
    strStyle += QString("QWidget#widgetWeek{ background-color: #efefef;}");
    strStyle += QString("QLabel#labelTitle {border: none; font: bold 18px;}");
    strStyle += QString("QLabel#labelWeek {border-top: 1px solid #c3c3c3; border-left: 1px solid #c3c3c3; font: bold 12px;}");
    strStyle += QString("QLabel#labelDay[weekend=true],QLabel#labelWeek[weekend=true]{color: red;}");
    strStyle += QString("QLabel#labelDay {border-top: 1px solid #c3c3c3; border-left: 1px solid #c3c3c3; font-size: 14px;}");
    strStyle += QString("QLabel#labelShowDay {color: yellow; font: bold 64px;}");
    strStyle += QString("QLabel#labelCommon {background-color: transparent;color: #ffffff;}");
    strStyle += QString("QLabel#labelSchedule {background-color: transparent;color: #ffffff; border: 1px solid #ffffff;}");
    strStyle += QString("QLabel#labelSpacer {border: 1px solid #ffffff;}");
    strStyle += QString("QLineEdit {border: 1px solid #ffffff; border-radius: 5px; font-size: 20px;}");

#else
    strStyle += QString(".CalendarWidget {border: 1px solid #ff00ff;}");
    strStyle += QString(".Window {background: black;}");
    strStyle += QString(".DayLabel{font: 24px; font-family: 隶书;}");
    strStyle += QString("QWidget#widgetCalendar{ background-color: white;}");
    strStyle += QString("QWidget#widgetTitle{ background-color: #c8b9a6;}");
    strStyle += QString("QWidget#widgetWeek{ background-color: #efefef;}");
    strStyle += QString("QLabel#labelTitle {border: none; font: bold 18px;}");
    strStyle += QString("QLabel#labelWeek {border-top: 1px solid #c3c3c3; border-left: 1px solid #c3c3c3; font: bold 12px;}");
    strStyle += QString("QLabel#labelDay[weekend=true],QLabel#labelWeek[weekend=true]{color: red;}");
    strStyle += QString("QLabel#labelDay {border-top: 1px solid #c3c3c3; border-left: 1px solid #c3c3c3; font-size: 14px;}");
    strStyle += QString("QLabel#labelShowDay {color: yellow; font: bold 64px;}");
    strStyle += QString("QLabel#labelCommon {color: #ffffff;}");
    strStyle += QString("QLabel#labelSchedule {color: #ffffff; border: 1px solid #ffffff;}");
    strStyle += QString("QLabel#labelSpacer {border: 1px solid #ffffff;}");
    strStyle += QString("QLineEdit {border: 1px solid #ffffff; border-radius: 5px; font-size: 20px;}");
#endif
    this->setStyleSheet(strStyle);
}

void Window::sltDayClicked(int nday)
{
    labelShowDay->setText(QString("%1").arg(nday, 2, 10, QChar('0')));
    // 显示农历
    QString strLunar = Date::getLunarMonAndDay(calendar->year(), calendar->month(), nday);
    labelShowLunarDate->setText(tr("农历  %1").arg(strLunar));
}

void Window::sltDayChanged()
{
    // 更新右边控件显示
    labelShowDay->setText(QString("%1").arg(calendar->day(), 2, 10, QChar('0')));
    // 显示农历
    QString strLunar = Date::getLunarMonAndDay(calendar->year(), calendar->month(), calendar->day());
    labelShowLunarDate->setText(tr("农历  %1").arg(strLunar));
    labelShowNYear->setText(Date::getLunarTime(calendar->year()));
}

// 跳转日期
void Window::sltDateJump()
{
    int year = editYearJump->text().toInt();
    int month = editMonthJump->text().toInt();
    int day = editDayJump->text().toInt();
    int nMaxSet = 0;

    if ((year > 2040) || (year < 1970)) {
        QMessageBox::information(this, tr("提示"), tr("跳转年输入错误，请重新输入！"));
        editYearJump->setFocus();
        return;
    }

    if ((month > 12) || (month < 1)) {
        editMonthJump->setFocus();
        QMessageBox::information(this, tr("提示"), tr("跳转月输入错误，请重新输入！"));
        return;
    }

    if (2 == month) {
        nMaxSet = Date::isLoopYaer(year) ? 29 : 28;
    }
    else {
        nMaxSet = 31;
    }

    if ((day > nMaxSet) || (day < 1)) {
        editDayJump->setFocus();
        QMessageBox::information(this, tr("提示"), tr("跳转日输入错误，请重新输入！"));
        return;
    }
    // 跳转
    calendar->jumpTodate(year, month, day);
}

/**
 * @brief Window::sltBack2today 跳转至今天
 */
void Window::sltBack2today()
{
    int year = QDate::currentDate().year();
    int month = QDate::currentDate().month();
    int day = QDate::currentDate().day();

    // 跳转
    calendar->jumpTodate(year, month, day);
}

/**
 * @brief Window::sltShowPlans 显示日程
 * @param content
 * @return
 */
void Window::sltShowPlans(const QString &content)
{
    labelShowPlan->setText(content);
}

void Window::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
