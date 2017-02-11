#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>
#include <QLabel>

QT_BEGIN_NAMESPACE
class QPushButton;
class QComboBox;
class QGroupBox;
class QLineEdit;
class QDate;
class QGridLayout;
class QHBoxLayout;
class QVBoxLayout;

class Event;
class DataBase;
QT_END_NAMESPACE

typedef enum {
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Week
} E_WEEK;

typedef enum {
    PREV_MONTH_DAY,     // 上月剩余天数
    NEXT_MONTH_DAY,     // 下个月的天数
    CURR_MONTH_DAY,     // 当月天数
    WEEKEND_DAY,        // 周末
    CURRENT_DAY,        // 当天
} E_DAY;

///////////////////////////////////////////////
/// \brief The DayLabel class
/// 自定义的日子显示控件
///////////////////////////////////////////////
class DayLabel : public QLabel {
    Q_OBJECT

public:
    explicit DayLabel(QWidget *parent = 0);

    bool bSelect;
    bool getBSelect() const;
    void setSelected(bool value);
    void setColor(const int &type);
    void showDay(int nDay, QString strLunar);

    int m_nDay;
    void setPlan(QStringList plan);
signals:
    void signalClicked(int ntype, int day);
    void signalPlan(const QString &content);
private:
    QLabel *labelIcon;
    QStringList m_strListPlan;
protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
};

/////////////////////////////////////////////////
/// \brief The CalendarWidget class
/// 日历界面
////////////////////////////////////////////////
class CalendarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalendarWidget(QWidget *parent = 0);
    ~CalendarWidget();

    int year() const;
    void setYear(int year);

    int month() const;
    void setMonth(int month);

    int day() const;
    void setDay(int day);

    void jumpTodate(int year, int month, int day);
signals:
    void signalDayClicked(int nday);
    void signalDayChanged();
    void signalPlan(const QString &content);
private:
    QVBoxLayout *verLayoutCalendar;

    QWidget *widgetTitle;
    QLabel *labelTitle;
    QPushButton *btnPrevMonth;
    QPushButton *btnNextMonth;
    QHBoxLayout *horLayoutTitle;

    QWidget *widgetWeek;
    QLabel *labelWeek[Week];
    QHBoxLayout *horLayoutWeek;

    QWidget *widgetBody;
    DayLabel *labelDay[42];
    QGridLayout *gridLayoutBody;

    QWidget *widgetRight;

    QLabel *labelShowToday;
    QLabel *labelShowWeek;
    QLabel *labelShowDay;
    QLabel *labelShowNYear;
    QLabel *labelShowLunarDate;
    QLabel *labelSpacer;
    QLabel *labelScheduleTitle;
    QLabel *labelSchedule;

    QVBoxLayout *verlayoutWidgetRight;

    QHBoxLayout *horLayoutGlobal;

private:
    int m_nYear;
    int m_nMonth;
    int m_nDay;
private:
    void initWidget();
    void initDate();
private slots:
    void sltDayClicked(int type, int day);
    void sltShowPrevMonth();
    void sltShowNextMonth();
};

////////////////////////////////////////
/// \brief The Window class
/// 万年历
///////////////////////////////////////
class Window : public QWidget {
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private:
    CalendarWidget *calendar;

    QWidget *widgetRight;

    QLabel *labelShowToday;
    QLabel *labelShowWeek;
    QLabel *labelShowDay;
    QLabel *labelShowNYear;
    QLabel *labelShowLunarDate;
    QLabel *labelSpacer;
    QLabel *labelPlanTitle;
    QLabel *labelShowPlan;

    QVBoxLayout *verlayoutWidgetRight;
    QHBoxLayout *horLayoutWidget;

    // 底部新增时间跳转设置，备注说明
    QGroupBox *groupBoxBottom;
    QLabel *labelYearJump;
    QLabel *labelMonthJump;
    QLabel *labelDayJump;

    QLineEdit *editYearJump;
    QLineEdit *editMonthJump;
    QLineEdit *editDayJump;

    QPushButton *btnDateJump;
    QPushButton *btnToday;

    QHBoxLayout *horLayoutJump;

    QVBoxLayout *verLayoutAll;
private:
    void initWidget();
    void initDatabase();
    void initStyle();
private slots:
    void sltDayClicked(int nday);
    void sltDayChanged();
    void sltDateJump();
    void sltBack2today();

    void sltShowPlans(const QString &content);
protected:
    void paintEvent(QPaintEvent *);
};

#endif // CALENDARWIDGET_H
