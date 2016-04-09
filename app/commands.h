#ifndef COMMANDS_H
#define COMMANDS_H

#include <QApplication>
#include <QGraphicsItem>
#include <QList>
#include <QPointF>
#include <QUndoCommand>
#include <memory>
#include <node.h>
#include <qneconnection.h>
class Scene;
class Editor;
class GraphicElement;

class AddItemsCommand : public QUndoCommand {
  Q_DECLARE_TR_FUNCTIONS( AddItemsCommand )

  enum { Id = 101 };
public:
  AddItemsCommand( GraphicElement *aItem, Editor *aEditor, QUndoCommand *parent = 0 );
  AddItemsCommand( QNEConnection *aItem, Editor *aEditor, QUndoCommand *parent = 0 );
  AddItemsCommand( const QList< QGraphicsItem* > &aItems, Editor *aEditor, QUndoCommand *parent = 0 );

  virtual void undo( ) Q_DECL_OVERRIDE;
  virtual void redo( ) Q_DECL_OVERRIDE;

private:
  QByteArray itemData;
  Editor *editor;
  bool firstRun;
  QVector< int > ids;
};

class DeleteItemsCommand : public QUndoCommand {
  Q_DECLARE_TR_FUNCTIONS( DeleteItemsCommand )
  enum { Id = 102 };
public:
  DeleteItemsCommand( const QList< QGraphicsItem* > &aItems, Editor *aEditor, QUndoCommand *parent = 0 );

  virtual void undo( ) Q_DECL_OVERRIDE;
  virtual void redo( ) Q_DECL_OVERRIDE;

private:
  QByteArray itemData;
  Editor *editor;
  QVector< int > ids;
};

class RotateCommand : public QUndoCommand {
  Q_DECLARE_TR_FUNCTIONS( RotateCommand )

  enum { Id = 103 };
public:
  RotateCommand( const QList< GraphicElement* > &aItems, int angle, QUndoCommand *parent = 0 );
  virtual void undo( ) Q_DECL_OVERRIDE;
  virtual void redo( ) Q_DECL_OVERRIDE;
  bool mergeWith( const QUndoCommand *command ) Q_DECL_OVERRIDE;
  int id( ) const Q_DECL_OVERRIDE;
private:
  int angle;
  QList< GraphicElement* > list;
  QList< QPointF > positions;
};


class MoveCommand : public QUndoCommand {
  Q_DECLARE_TR_FUNCTIONS( MoveCommand )
public:
  enum { Id = 104 };

  MoveCommand( const QList< GraphicElement* > &list, const QList< QPointF > &aOldPositions, QUndoCommand *parent = 0 );

  virtual void undo( ) Q_DECL_OVERRIDE;
  virtual void redo( ) Q_DECL_OVERRIDE;
  int id( ) const Q_DECL_OVERRIDE {
    return( Id );
  }

private:
  QList< GraphicElement* > myList;
  QList< QPointF > oldPositions;
  QList< QPointF > newPositions;

  QPointF offset;
};

class UpdateCommand : public QUndoCommand {
  Q_DECLARE_TR_FUNCTIONS( UpdateCommand )
public:
  enum { Id = 105 };

  UpdateCommand( const QVector< GraphicElement* > &elements, QByteArray oldData, QUndoCommand *parent = 0 );

  virtual void undo( ) Q_DECL_OVERRIDE;
  virtual void redo( ) Q_DECL_OVERRIDE;
  int id( ) const Q_DECL_OVERRIDE {
    return( Id );
  }

private:
  QVector< GraphicElement* > m_elements;
  QByteArray m_oldData;
  QByteArray m_newData;

  void loadData( QByteArray itemData );
};

class SplitCommand : public QUndoCommand {
  Q_DECLARE_TR_FUNCTIONS( SplitCommand )
  enum { Id = 106 };

public:

  SplitCommand( QNEConnection *conn, QPointF point, QUndoCommand *parent = 0 );
  virtual ~SplitCommand( );
  virtual void undo( ) Q_DECL_OVERRIDE;
  virtual void redo( ) Q_DECL_OVERRIDE;

private:
  QNEConnection *c1;
  QNEConnection *c2;
  QNEPort *p1, *p2;
  QNEPort *trueP1, *trueP2;

  Node *node;
};

class MorphCommand : public QUndoCommand {
  Q_DECLARE_TR_FUNCTIONS( MorphCommand )
public:
  enum { Id = 107 };

  MorphCommand( const QVector< GraphicElement* > &elements, ElementType type, Editor *editor,
                QUndoCommand *parent = 0 );

  virtual void undo( ) Q_DECL_OVERRIDE;
  virtual void redo( ) Q_DECL_OVERRIDE;
  int id( ) const Q_DECL_OVERRIDE {
    return( Id );
  }

private:
  QVector< GraphicElement* > old_elements;
  QVector< GraphicElement* > new_elements;
  QGraphicsScene *scene;
  void transferConnections( QVector< GraphicElement* > from, QVector< GraphicElement* > to );
};

class ChangeInputSZCommand : public QUndoCommand {
  Q_DECLARE_TR_FUNCTIONS( ChangeInputSZCommand )
public:
  enum { Id = 108 };

  ChangeInputSZCommand( const QVector< GraphicElement* > &elements, int newInputSize, QUndoCommand *parent = 0 );

  virtual void undo( ) Q_DECL_OVERRIDE;
  virtual void redo( ) Q_DECL_OVERRIDE;
  int id( ) const Q_DECL_OVERRIDE {
    return( Id );
  }

private:
  QVector< GraphicElement* > m_elements;
  QVector< GraphicElement* > serializationOrder;
  QVector< QNEConnection* > storedConnections;
  QGraphicsScene *scene;
  QByteArray m_oldData;
  int m_newInputSize;

};

#endif /* COMMANDS_H */
