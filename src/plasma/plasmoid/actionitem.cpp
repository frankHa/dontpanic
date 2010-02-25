#include "actionitem.h"
#include "detail/action.h"
#include "detail/actiondescription.h"
#include "plasma-dontpanic.h"
#include <libdontpanic/durationformatter.h>
#include <Plasma/Label>
#include <Plasma/Separator>
#include <Plasma/IconWidget>
#include <Plasma/ScrollWidget>
#include <Plasma/Animator>
#include <Plasma/Animation>
#include <QGraphicsLinearLayout>
#include <QGraphicsSceneHoverEvent>
#include <KGlobalSettings>
#include <KAction>
namespace dp
{
namespace plasma
{
namespace applet
{
static const int MARGIN = 3;
ActionItem::ActionItem ( QGraphicsWidget *parent, PlasmaDontPanic *applet )
        :QGraphicsWidget ( parent )
        , _M_applet ( applet )
        , _M_current_action()
        , _M_action_description ( 0 )
        , _M_possible_actions ( 0 )
        , _M_tree_layout ( 0 )
        , _M_scroll(0)
        , _M_actions_widget ( 0 )
        , _M_actions_layout ( 0 )
        ,_M_label_fade ( 0 )
        ,_M_hovered ( false )
{
    connect ( applet, SIGNAL ( currentActionChanged ( detail::Action const& ) ), this, SLOT ( setAction ( detail::Action const& ) ) );
    this->setAcceptHoverEvents ( true );
    setCacheMode ( DeviceCoordinateCache );
    setZValue ( 0 );
    _M_tree_layout = new QGraphicsLinearLayout ( Qt::Vertical, this );
    _M_tree_layout->setContentsMargins ( 0, 0, 0, 0 );

    _M_action_description = new Plasma::Label ( this );
    _M_possible_actions = new Plasma::Label ( this );

    QFont font = _M_possible_actions->font();
    font.setPointSize ( KGlobalSettings::smallestReadableFont().pointSize() );
    font.setItalic ( true );
    _M_possible_actions->setFont ( font );
    _M_possible_actions->setOpacity ( 0 );
    _M_possible_actions->setAlignment ( Qt::AlignRight );

    QGraphicsLinearLayout *info = new QGraphicsLinearLayout ( Qt::Vertical );
    info->addItem ( _M_action_description );
    info->addItem ( _M_possible_actions );
    info->setSpacing ( 0 );

    _M_tree_layout->addItem ( info );

    _M_scroll = new Plasma::ScrollWidget(this);
    _M_actions_widget = new QGraphicsWidget ( _M_scroll );
    _M_scroll->setWidget(_M_actions_widget);
    //scroll->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    //_M_actions_widget->hide();
    _M_actions_layout = new QGraphicsLinearLayout ( Qt::Vertical, _M_actions_widget );
    _M_actions_layout->setContentsMargins ( 30, 0, 0, 0 );
    //_M_tree_layout->addItem ( _M_actions_widget );
    _M_tree_layout->addItem(_M_scroll);
    setAction ( _M_current_action );


}

ActionItem::~ActionItem() {}

void ActionItem::setAction ( const detail::Action& action )
{
    _M_current_action = action;
    setActionDescription ( _M_current_action );
    initPossibleActionsFor ( _M_current_action );
}


void ActionItem::setActionDescription ( detail::Action const& action )
{
    _M_action_description->setText(detail::actionDescription().forAction(action));
}

void ActionItem::setHovered ( bool hovered )
{
    if ( hovered == _M_hovered )
    {
        return;
    }
    _M_hovered = hovered;

    int targetOpacity = ( hovered ) ?100:0;
    if ( !_M_label_fade )
    {
        _M_label_fade = Plasma::Animator::create ( Plasma::Animator::FadeAnimation, this );

        _M_label_fade->setTargetWidget ( _M_possible_actions );
    }
    _M_label_fade->setProperty ( "targetOpacity", targetOpacity );
    qreal currentOpacity = _M_action_description->opacity();
    _M_label_fade->setProperty ( "startOpacity", currentOpacity );
    _M_label_fade->start();

}
void ActionItem::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
    setHovered ( true );
}
void ActionItem::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
{
    setHovered ( false );
}

void ActionItem::expand()
{
    if ( !isCollapsed() )
    {
        return;
    }
    _M_tree_layout->addItem ( _M_scroll );
    _M_scroll->show();
    update();
}
void ActionItem::collapse()
{
    if ( isCollapsed() )
    {
        return;
    }
    _M_tree_layout->removeItem ( _M_scroll );
    _M_scroll->hide();
    update();
}

bool ActionItem::isCollapsed() const
{
    return ( _M_tree_layout->count() == 1 );
}

void ActionItem::initPossibleActionsFor ( detail::Action const&a )
{
    bool wasExpanded = !isCollapsed();
    collapse();
    removePossibleActions();
    addPossibleActionsFor ( a );
    if ( wasExpanded )
    {
        expand();
    }
}

void ActionItem::removePossibleActions()
{
    while ( _M_actions_layout->count() > 0 )
    {
        QGraphicsLayoutItem *item = _M_actions_layout->itemAt ( 0 );
        _M_actions_layout->removeAt ( 0 );
        delete item;
    }
}

void ActionItem::addPossibleActionsFor ( const dp::plasma::applet::detail::Action& a )
{
    addPossibleAction ( applet()->start_new_action() );
    addPossibleAction ( applet()->resume_last_action() );
    if ( a.active )
    {
        addPossibleAction ( applet()->stop_current_action() );
    }
    _M_actions_layout->addItem ( new Plasma::Separator ( this ) );
    Plasma::Label *l = new Plasma::Label(this);
    l->setText(i18n("switch activity to:"));
    _M_actions_layout->addItem(l);
    _M_actions_layout->addItem ( new Plasma::Separator ( this ) );
    
    foreach(detail::Favorite const& fav, applet()->favorites())
    {
      addPossibleAction(applet()->action_for(fav));
    }
    updatePossibleActionsText();
}

void ActionItem::addPossibleAction ( KAction *action )
{
    Plasma::IconWidget *action_widget = new Plasma::IconWidget ( _M_actions_widget );
    action_widget->setAction ( action );
    action_widget->setOrientation(Qt::Horizontal);
    action_widget->setPreferredHeight(KIconLoader::SizeSmall + 3 +3);
    action_widget->setPreferredWidth(0);
    action_widget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    _M_actions_layout->addItem ( action_widget );
}

void ActionItem::updatePossibleActionsText()
{
  static int const PASSIVE_LAYOUT_ITEMS = 3;
  _M_possible_actions->setText(i18n("%1 possible actions...").arg(_M_actions_layout->count() -  PASSIVE_LAYOUT_ITEMS));
}


PlasmaDontPanic *ActionItem::applet()
{
    return _M_applet;
}
}
}
}
#include "actionitem.moc"
