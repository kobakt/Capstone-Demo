import QtQuick
import QtQuick3D 6.0
import Cylinder 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Component {
        id: component3D
        Node {
            id: componentRoot
        }
    }

    View3D {
        id: view3D
        x: 128
        y: 48
        width: 400
        height: 400
        environment: sceneEnvironment
        SceneEnvironment {
            id: sceneEnvironment
            antialiasingMode: SceneEnvironment.MSAA
            antialiasingQuality: SceneEnvironment.High
        }

        Node {
            id: scene
            DirectionalLight {
                id: directionalLight
            }

            PerspectiveCamera {
                id: sceneCamera
                z: 350
            }

            Model {
                id: cubeModel
                x: -102.667
                y: 9.212
                visible: true
                source: "#Cube"
                z: -12.95184
                materials: [defaultMaterial]
                eulerRotation.y: 45
                eulerRotation.x: 30
            }

            DefaultMaterial {
                id: defaultMaterial
                diffuseColor: "#4aee45"
            }

            Model {
                id: cylinderModel
                x: -0
                y: 0
                visible: true
                scale: Qt.vector3d(100, 100, 100)
                geometry: Cylinder {
                    normals: true //cbNorm.checked
                    normalXY: 0.0 //sliderNorm.value
                    uv: false //cbUV.checked
                    uvAdjust: 0.0 //sliderUV.value
                }
                materials: [defaultMaterial]
            }
        }
    }
}
