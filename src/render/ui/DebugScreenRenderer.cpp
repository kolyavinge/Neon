#include <common/constants.h>
#include <lib/calc/UnitConverter.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Axle.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Chassis.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/VehicleData.h>
#include <model/vehicle/Wheel.h>
#include <render/gl/opengl.h>
#include <render/ui/DebugScreenRenderer.h>

void DebugScreenRenderer::setScreen(DebugScreen& screen) {
    _screen = &screen;
}

void DebugScreenRenderer::render() {
    GameState& gameState = _screen->getGameState();
    Vehicle& vehicle = gameState.getPlayerVehicle();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(CommonConstants::verticalFieldOfViewDegrees, CommonConstants::screenAspect, CommonConstants::zNear, CommonConstants::zFar);
    Vector3 eyePosition = vehicle.getDriveAxle().getCenter();
    eyePosition.subMultiplied(vehicle.getChassis().getFrontNormal(), 5.0f);
    eyePosition.addMultiplied(vehicle.getChassis().getRightNormal(), 3.0f);
    eyePosition.z += 4.0f;
    gluLookAt(eyePosition, vehicle.getNonDriveAxle().getCenter(), CommonConstants::upVector);
    renderGrid();
    //renderGlobalAxis();
    renderVehicle(vehicle);
}

void DebugScreenRenderer::renderVehicle(Vehicle& vehicle) {
    renderVehicleAxles(vehicle);
    renderVehicleWheels(vehicle);
    renderVehicleBody(vehicle);
    //renderVehicleAxis(vehicle);
}

void DebugScreenRenderer::renderVehicleAxles(Vehicle& vehicle) {
    Axle& driveAxle = vehicle.getDriveAxle();
    Axle& nonDriveAxle = vehicle.getNonDriveAxle();
    // axle axis
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    glVertex3f(nonDriveAxle.getLeftWheelPosition());
    glVertex3f(nonDriveAxle.getRightWheelPosition());
    glVertex3f(driveAxle.getLeftWheelPosition());
    glVertex3f(driveAxle.getRightWheelPosition());
    glEnd();
    // axle points
    glPointSize(5.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    glVertex3f(driveAxle.getCenter());
    glEnd();
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POINTS);
    glVertex3f(nonDriveAxle.getCenter());
    glEnd();
    // driveAxle velocity
    glColor3f(0.0f, 1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(driveAxle.getCenter());
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    Vector3 velocity = driveAxle.getVelocity();
    velocity.div(10.0f);
    glVertex3f(velocity);
    glEnd();
    glPopMatrix();
    // nonDriveAxle velocity
    glColor3f(0.0f, 1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(nonDriveAxle.getCenter());
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    velocity = nonDriveAxle.getVelocity();
    velocity.div(10.0f);
    glVertex3f(velocity);
    glEnd();
    glPopMatrix();
}

void DebugScreenRenderer::renderVehicleWheels(Vehicle& vehicle) {
    VehicleData& vehicleData = vehicle.getData();
    Chassis& chassis = vehicle.getChassis();
    for (int i = 0; i < vehicle.wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        Spring& spring = vehicle.getSpring(i);
        glColor3f(0.8f, 0.8f, 0.8f);
        // wheel circle
        glPushMatrix();
        glTranslatef(wheel.getCenter());
        glRotatef(UnitConverter::radiansToDegrees(wheel.getSteeringAngle()), chassis.getTopNormal());
        glRotatef(UnitConverter::radiansToDegrees(chassis.getRotateAngle()), chassis.getRotateAxis());
        glDrawCircleYZ(vehicleData.radius, 16);
        glPopMatrix();
        // angle line
        glPushMatrix();
        glTranslatef(wheel.getCenter());
        glRotatef(UnitConverter::radiansToDegrees(wheel.getRotateAngle()), wheel.getOutsdteNormal());
        glRotatef(UnitConverter::radiansToDegrees(wheel.getSteeringAngle()), chassis.getTopNormal());
        glRotatef(UnitConverter::radiansToDegrees(chassis.getRotateAngle()), chassis.getRotateAxis());
        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, vehicleData.radius, 0.0f);
        glEnd();
        glPopMatrix();
        // front normal
        glPushMatrix();
        glTranslatef(wheel.getCenter());
        glColor3f(0.0f, 0.8f, 0.0f);
        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        Vector3 frontNormal = wheel.getFrontNormal();
        frontNormal.setLength(0.5f);
        glVertex3f(frontNormal);
        glEnd();
        glPopMatrix();
        // outside normal
        glPushMatrix();
        glTranslatef(wheel.getCenter());
        glColor3f(0.0f, 0.8f, 0.0f);
        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        Vector3 outsideNormal = wheel.getOutsdteNormal();
        outsideNormal.setLength(0.5f);
        glVertex3f(outsideNormal);
        glEnd();
        glPopMatrix();
        // longitudinal force
        glColor3f(1.0f, 0.0f, 0.0f);
        glPushMatrix();
        glTranslatef(wheel.getCenter());
        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        Vector3 longitudinalForce = wheel.getLongitudinalForce();
        longitudinalForce.div(_forceDivider);
        glVertex3f(longitudinalForce);
        glEnd();
        glPopMatrix();
        // lateral force
        glColor3f(0.0f, 0.0f, 1.0f);
        glPushMatrix();
        glTranslatef(wheel.getCenter());
        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        Vector3 lateralForce = wheel.getLateralForce();
        lateralForce.div(_forceDivider);
        glVertex3f(lateralForce);
        glEnd();
        glPopMatrix();
        // spring force
        glColor3f(1.0f, 0.0f, 0.0f);
        glPushMatrix();
        glTranslatef(wheel.getCenter());
        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        float springForce = spring.getForce();
        springForce /= _forceDivider;
        glVertex3f(0.0f, 0.0f, -springForce);
        glEnd();
        glPopMatrix();
        // linear velocity
        //if (!wheel.getLinearVelocity().isZero()) {
        //    glPushMatrix();
        //    glTranslatef(wheel.getCenter());
        //    glColor3f(0.8f, 0.8f, 0.0f);
        //    glBegin(GL_LINES);
        //    glVertex3f(0.0f, 0.0f, 0.0f);
        //    Vector3 linearVelocity = wheel.getLinearVelocity();
        //    linearVelocity.setLength(0.5f);
        //    glVertex3f(linearVelocity);
        //    glEnd();
        //    glPopMatrix();
        //}
    }
}

void DebugScreenRenderer::renderVehicleBody(Vehicle& vehicle) {
    Body& body = vehicle.getBody();
    Axle& nonDriveAxle = vehicle.getNonDriveAxle();
    // air drag force
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(nonDriveAxle.getCenter());
    glTranslatef(0.0f, 0.0f, 1.5f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    Vector3 airDragForce = body.getAirDragForce();
    airDragForce.div(_forceDivider);
    glVertex3f(airDragForce);
    glEnd();
    glPopMatrix();
}

void DebugScreenRenderer::renderVehicleAxis(Vehicle& vehicle) {
    Chassis& chassis = vehicle.getChassis();
    Axle& driveAxle = vehicle.getDriveAxle();

    glPushMatrix();
    glTranslatef(driveAxle.getCenter());
    glBegin(GL_LINES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(chassis.getRightNormal());

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(chassis.getFrontNormal());

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(chassis.getTopNormal());

    glEnd();
    glPopMatrix();
}

void DebugScreenRenderer::renderGrid() {
    const float length = 10.0f * CommonConstants::zFar;
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_LINES);
    for (float step = -length; step < length; step += 1.0f) {
        glVertex3f(step, -length, 0.0f);
        glVertex3f(step, length, 0.0f);
        glVertex3f(-length, step, 0.0f);
        glVertex3f(length, step, 0.0f);
    }
    glEnd();
}

void DebugScreenRenderer::renderGlobalAxis() {
    glBegin(GL_LINES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);

    glEnd();
}
