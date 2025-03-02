#pragma once

#include <QtCore/QJsonDocument>
#include <QtCore/QUuid>
#include <QtWidgets/QGraphicsScene>
#include <functional>
#include <tuple>
#include <unordered_map>

#include "DataModelRegistry.hpp"
#include "Export.hpp"
#include "QUuidStdHash.hpp"
#include "TypeConverter.hpp"
#include "memory.hpp"

namespace QtNodes {

class NodeDataModel;
class FlowItemInterface;
class Node;
class NodeGraphicsObject;
class Connection;
class ConnectionGraphicsObject;
class NodeStyle;

/// Scene holds connections and nodes.
class NODE_EDITOR_PUBLIC FlowScene : public QGraphicsScene {
  Q_OBJECT
 public:
  FlowScene(std::shared_ptr<DataModelRegistry> registry,
            QObject* parent = Q_NULLPTR);

  FlowScene(QObject* parent = Q_NULLPTR);

  ~FlowScene() override;

 public:
  std::shared_ptr<Connection>
  createConnection(PortType connectedPort,
                   Node& node,
                   PortIndex portIndex,
                   bool isAPreview = false,
                   void* data = nullptr);

  std::shared_ptr<Connection>
  createConnection(Node& nodeIn,
                   PortIndex portIndexIn,
                   Node& nodeOut,
                   PortIndex portIndexOut,
                   TypeConverter const& converter = TypeConverter{},
                   bool isAPreview = false,
                   void* data = nullptr);

  std::shared_ptr<Connection>
  restoreConnection(QJsonObject const& connectionJson);

  void deleteConnection(Connection& connection);

  Node& createNode(std::unique_ptr<NodeDataModel>&& dataModel);

  Node& restoreNode(QJsonObject const& nodeJson);

  void removeNode(Node& node);

  DataModelRegistry& registry() const;

  void setRegistry(std::shared_ptr<DataModelRegistry> registry);

  void iterateOverNodes(std::function<void(Node*)> const& visitor);

  void iterateOverNodeData(std::function<void(NodeDataModel*)> const& visitor);

  void iterateOverNodeDataDependentOrder(std::function<void(NodeDataModel*)> const& visitor);

  QPointF getNodePosition(Node const& node) const;

  void setNodePosition(Node& node, QPointF const& pos) const;

  QSizeF getNodeSize(Node const& node) const;

  // MK : use read only property for the scene
  void setReadOnly(bool ro);

  bool isReadOnly() const;

 public:
  std::unordered_map<QUuid, std::unique_ptr<Node> > const& nodes() const;

  std::unordered_map<QUuid, std::shared_ptr<Connection> > const& connections() const;

  std::vector<Node*> allNodes() const;

  std::vector<Node*> selectedNodes() const;

 public:
  void clearScene();

  /// @name File IO
  ///
  /// These functions are for saving to and loading from files.
  ///
  /// @note These functions will launch a file dialog to retrieve a suitable
  /// path for the JSON document.
  ///
  /// @{

  /// Open a FileDialog to save the scene in a .flow file
  void save() const;

  /// Load a FileDialog to open a scene from a .flow file
  void load();

  /// @name Memory IO
  ///
  /// These functions are for saving to and loading from memory.
  ///
  /// @{

  /// Dump the scene on a JSON QByteArray
  QByteArray saveToMemory(
      QJsonDocument::JsonFormat format = QJsonDocument::Indented) const;

  /// Load a scene from a JSON QByteArray
  void loadFromMemory(const QByteArray& data);

  /// @}

  /// @name JSON Object IO
  ///
  /// These functions are for saving to and loading from JSON objects.
  /// This is useful when embedding the nodes and their connections into a
  /// JSON document that contains other data.
  ///
  /// @{

  /// Dump the scene on a JSON Object.
  QJsonObject saveToObject() const;

  /// Load a scene from a JSON Object
  void loadFromObject(const QJsonObject& data);

  /// Load a scene from a JSON Object
  ///
  /// @note Internally this is just an alias for @ref FlowScene::loadFromObject.
  /// It is kept for backwards compatibility.
  void loadFromMemory(const QJsonObject& data);

  /// @}

  /// Save only a subset of the nodes to memory, as well as the connections that
  /// link two nodes lying within this subset.
  QByteArray copyNodes(const std::vector<Node*>& nodes) const;

  //! Paste selected nodes to the scene replacing uuids with new ones with a
  //! certain offset from the original position.
  void pasteNodes(const QByteArray& data,
                  const QPointF& pointOffset = QPointF(0, 0));

 Q_SIGNALS:

  /**
   * @brief Node has been created but not on the scene yet.
   * @see nodePlaced()
   */
  void nodeCreated(Node& n);

  /**
   * @brief Node has been added to the scene.
   * @details Connect to this signal if need a correct position of node.
   * @see nodeCreated()
   */
  void nodePlaced(Node& n);

  void nodeDeleted(Node& n);

  void connectionCreated(Connection const& c);
  void connectionDeleted(Connection const& c);

  void nodeMoved(Node& n, const QPointF& newLocation);

  void nodeDoubleClicked(Node& n);

  void nodeSelected(Node& n);  // MK : new method

  void connectionHovered(Connection& c, QPoint screenPos);
  void connectionSelected(Connection& c);  // MK : new method
  void connectionDoubleClicked(Connection& c);  // MK : new method

  void nodeHovered(Node& n, QPoint screenPos);

  void connectionHoverLeft(Connection& c);

  void nodeHoverLeft(Node& n);

  void nodeContextMenu(Node& n, const QPointF& pos);

 private:
  using SharedConnection = std::shared_ptr<Connection>;
  using UniqueNode = std::unique_ptr<Node>;

  // DO NOT reorder this member to go after the others.
  // This should outlive all the connections and nodes of
  // the graph, so that nodes can potentially have pointers into it,
  // which is why it comes first in the class.
  std::shared_ptr<DataModelRegistry> _registry;

  std::unordered_map<QUuid, SharedConnection> _connections;
  std::unordered_map<QUuid, UniqueNode> _nodes;
  bool _readOnly;

 private Q_SLOTS:

  void setupConnectionSignals(Connection const& c);

  void sendConnectionCreatedToNodes(Connection const& c);
  void sendConnectionDeletedToNodes(Connection const& c);
};

Node*
locateNodeAt(QPointF scenePoint, FlowScene& scene,
             QTransform const& viewTransform);
}  // namespace QtNodes
