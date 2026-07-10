#include <common/constants.h>
#include <debug/DebugRenderer.h>
#include <lib/calc/UnitConverter.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Axle.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Chassis.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Wheel.h>
#include <render/lib/opengl.h>

void DebugRenderer::renderDebugInfo(GameState& gameState) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    Camera& camera = gameState.getCamera();
    gluPerspective(
        UnitConverter::radiansToDegrees(camera.getVerticalViewAngle()),
        CommonConstants::screenAspect,
        CommonConstants::minPerspectiveDepth,
        CommonConstants::maxPerspectiveDepth);
    Vector3 lookAtPosition = camera.getPosition();
    lookAtPosition.add(camera.getLookDirection());
    gluLookAt(camera.getPosition(), lookAtPosition, CommonConstants::upVector);
    renderGrid();
    //renderGlobalAxis();
    Vehicle& vehicle = gameState.getPlayerVehicle();
    //renderVehicleAxles(vehicle);
    //renderVehicleWheels(vehicle);
    //renderVehicleBody(vehicle);
    //renderVehicleAxis(vehicle);
}

void DebugRenderer::renderVehicleAxles(Vehicle& vehicle) {
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
    velocity.div(_velocityDivider);
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
    velocity.div(_velocityDivider);
    glVertex3f(velocity);
    glEnd();
    glPopMatrix();
    // vehicle velocity
    glColor3f(0.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(driveAxle.getCenter());
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    velocity = vehicle.getLinearVelocity();
    velocity.div(_velocityDivider);
    glVertex3f(velocity);
    glEnd();
    glPopMatrix();
}

void DebugRenderer::renderVehicleWheels(Vehicle& vehicle) {
    Chassis& chassis = vehicle.getChassis();
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        Spring& spring = vehicle.getSpring(i);
        glColor3f(0.8f, 0.8f, 0.8f);
        // wheel circle
        glPushMatrix();
        glTranslatef(wheel.getCenter());
        glRotatef(UnitConverter::radiansToDegrees(wheel.getSteeringAngle()), chassis.getTopNormal());
        glRotatef(UnitConverter::radiansToDegrees(chassis.getRotateAngle()), chassis.getRotateAxis());
        glDrawCircleYZ(wheel.getRadius(), 16);
        glPopMatrix();
        // angle line
        glPushMatrix();
        glTranslatef(wheel.getCenter());
        glRotatef(UnitConverter::radiansToDegrees(wheel.getRotateAngle()), wheel.getOutsdteNormal());
        glRotatef(UnitConverter::radiansToDegrees(wheel.getSteeringAngle()), chassis.getTopNormal());
        glRotatef(UnitConverter::radiansToDegrees(chassis.getRotateAngle()), chassis.getRotateAxis());
        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, wheel.getRadius(), 0.0f);
        glEnd();
        glPopMatrix();
        // front normal
        //glPushMatrix();
        //glTranslatef(wheel.getCenter());
        //glColor3f(0.0f, 0.8f, 0.0f);
        //glBegin(GL_LINES);
        //glVertex3f(0.0f, 0.0f, 0.0f);
        //Vector3 frontNormal = wheel.getFrontNormal();
        //frontNormal.setLength(0.5f);
        //glVertex3f(frontNormal);
        //glEnd();
        //glPopMatrix();
        // outside normal
        //glPushMatrix();
        //glTranslatef(wheel.getCenter());
        //glColor3f(0.0f, 0.8f, 0.0f);
        //glBegin(GL_LINES);
        //glVertex3f(0.0f, 0.0f, 0.0f);
        //Vector3 outsideNormal = wheel.getOutsdteNormal();
        //outsideNormal.setLength(0.5f);
        //glVertex3f(outsideNormal);
        //glEnd();
        //glPopMatrix();
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

void DebugRenderer::renderVehicleBody(Vehicle& vehicle) {
    // body box
    Body& body = vehicle.getBody();
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(body.getBox().getBottomRect().downLeft);
    glVertex3f(body.getBox().getBottomRect().downRight);
    glVertex3f(body.getBox().getBottomRect().upRight);
    glVertex3f(body.getBox().getBottomRect().upLeft);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(body.getBox().getTopRect().downLeft);
    glVertex3f(body.getBox().getTopRect().downRight);
    glVertex3f(body.getBox().getTopRect().upRight);
    glVertex3f(body.getBox().getTopRect().upLeft);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(body.getBox().getBottomRect().downLeft);
    glVertex3f(body.getBox().getTopRect().downLeft);
    glVertex3f(body.getBox().getBottomRect().downRight);
    glVertex3f(body.getBox().getTopRect().downRight);
    glVertex3f(body.getBox().getBottomRect().upLeft);
    glVertex3f(body.getBox().getTopRect().upLeft);
    glVertex3f(body.getBox().getBottomRect().upRight);
    glVertex3f(body.getBox().getTopRect().upRight);
    glEnd();
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

void DebugRenderer::renderVehicleAxis(Vehicle& vehicle) {
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

void DebugRenderer::renderGrid() {
    glEnable(GL_DEPTH_TEST);
    const float length = 10.0f * CommonConstants::maxPerspectiveDepth;
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_LINES);
    for (float step = -length; step < length; step += 1.0f) {
        glVertex3f(step, -length, 0.0f);
        glVertex3f(step, length, 0.0f);
        glVertex3f(-length, step, 0.0f);
        glVertex3f(length, step, 0.0f);
    }
    glEnd();
    glDisable(GL_DEPTH_TEST);
}

void DebugRenderer::renderGlobalAxis() {
    float axisLength = 10.0f;
    float color = 0.8f;

    glBegin(GL_LINES);

    glColor3f(color, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(axisLength, 0.0f, 0.0f);

    glColor3f(0.0f, color, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, axisLength, 0.0f);

    glColor3f(0.0f, 0.0f, color);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, axisLength);

    glEnd();
}
