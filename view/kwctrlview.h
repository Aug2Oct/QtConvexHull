#ifndef KWCTRLVIEW_H
#define KWCTRLVIEW_H

#include <QWidget>
#include <QPainterPath>

# ifndef ARM
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>


#define TEXTURE_NUM 2

class KWCtrlView
        : public QOpenGLWidget
        , protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit KWCtrlView(QWidget *parent = nullptr);
    ~KWCtrlView() override;

    virtual void ResetView();

    void SetCoordMirrorX(bool bMirror);
    void SetCoordMirrorY(bool bMirror);

    ///����
    void ViewPoint(const QPointF & pt);
    void ScrPint(const QPointF & pt);
    void glColor(const QColor& clr);

    ///����ת��
    void Scr2View(QPointF &pt);
    void View2Scr(QPointF &pt);

    bool IsTextureVisiable(int i);
    void SetTextureVisiable(int i, bool isVisable);
    void SetTextureOffset(int i, double x = 0, double y = 0);

protected:
    ///����ʵ�ִ˽ӿ�,��ͼ
    virtual void DrawGLSence(QPainter &/*painter*/) {}
    virtual void MouseLButtonPressed(QPointF &/*ptView*/, QPointF &/*ptScr*/){}
    virtual void MouseLButtonReleased(QPointF &/*ptView*/, QPointF &/*ptScr*/){}
    virtual void MouseRButtonPressed(QPointF &/*ptView*/, QPointF &/*ptScr*/){}
    virtual void MouseRButtonReleased(QPointF &/*ptView*/, QPointF &/*ptScr*/){}
    virtual void MouseMove(QPointF &/*ptView*/, QPointF &/*ptScr*/){  update();}
    virtual void MouseLDoubleClick(QPointF &/*ptView*/, QPointF &/*ptScr*/){}
    virtual void MouseRDoubleClick(QPointF &/*ptView*/, QPointF &/*ptScr*/){}
    virtual void Initialize(){}

    ///���̶���
    void DrawTick(QPainter &painter);

    ///��ԭ���־
    void DrawOrigin(QPainter &painter);

    ///�����ʮ�ּ�
    void DrawCross();

    void ScaleAndTrans(QPointF &pt);
    void Scale(QPointF &pt);
    void Trans(QPointF &pt);
    ///����ͷ
    void DrawArrow(const QPointF &ptStart, const QPointF &ptEnd,
                   bool bBoth = false, int arrowsize = 10, float lineW = 1);

    void DrawSelectBox();


protected:
    ///��ʼ��Opengl
    void initializeGL() override;

    ///���ڴ�С�ı�
    void resizeGL(int width,int height) override;

    void paintGL() override;//�ػ�

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void enterEvent(QEvent *evt) override;
    void leaveEvent(QEvent *evt) override;

    void BindTexture(const QImage &pix, int i);
    void DrawTexture(int i);

signals:



protected:
    bool m_bShowTick = true;
    bool m_bshowOrigin = true;
    bool m_bShowCross = true;
    bool m_bShowSelBox = true;
    bool m_bCoordMirrorY = false;
    bool m_bCoordMirrorX = false;

    bool m_bActiveMouse = false;
    bool m_bLButtonDown = false;	 /// ����Ƿ���
    bool m_bRButtonDown = false;     /// �Ҽ��Ƿ���

    float m_fScale = 1.0f;            /// ���ű���
    float m_fZoomStep = 0.25;
    float m_fLineWidth = 1.0;         /// �߿�
    float m_fPointSize = 1.5;          ///���С

    double m_dXTrans = 0.0, m_dXTransOld = 0.0;
    double m_dYTrans = 0.0, m_dYTransOld = 0.0;
    double m_dViewH = 300, m_dViewW = 300;

    GLuint m_texture[TEXTURE_NUM] = {0, 0};
    bool m_bTextureVisable[TEXTURE_NUM] {false, false};
    QImage m_imgTexture[TEXTURE_NUM];
    QPointF m_ptTextureOffset[TEXTURE_NUM];

    std::vector<GLuint> m_vecTex;

    QRectF m_rect{-100, 100, -100, 100};
    QRectF m_rectSelectingBox;
    QPointF m_ptOrigin = QPointF(0.0, 0.0); //ԭ��
    QPointF m_ptStart, m_ptEnd;
    QPointF m_ptCurCursor;///��ǰ���λ��;

    QColor m_clrTick {"#cccccc"};
    QColor m_clrBackGround {"#000000"};
    QFont m_fontSong = QFont("����", 11, QFont::DemiBold);
    QPixmap m_painterPix;
};

# else
#include "GrShapeSet.h"

class KWCtrlView : public QWidget
{
    Q_OBJECT
public:
    explicit KWCtrlView(QWidget *parent = nullptr);
    virtual ~KWCtrlView();

    virtual void ResetView();
    void SetShapeSet(const GrShapeSetSPtr &pShapeSet);

    void RestoreMode();
    void UpdateMode();
    void setSortedFlag(bool b);
    void SetMultipSel(bool b);
    void EnterDrawMode(int nMode);
    void SetShapeTechnology(int nTech);

private:
    void paintEvent(QPaintEvent *evt) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *evt) override;
    void mouseReleaseEvent(QMouseEvent *evt) override;
    void timerEvent(QTimerEvent *evt) override;

private:
    QMatrix m_matrix;
    QPainterPath m_drawPath;
    QRect _window;
    bool m_bLButtonDown = false;	 /// ����Ƿ���
    bool m_bRButtonDown = false;     /// �Ҽ��Ƿ���
    double offset = 0;
    QBasicTimer m_tmUpdate;
    QPixmap m_pix;

};

# endif

#endif // KWCTRLVIEW_H
