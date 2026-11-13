#include <render/lib/FrameStopwatch.h>

FrameStopwatch::FrameStopwatch() {
    _prevFrame = 0;
    _currentFrame = 0;
    _queryId[0] = 0;
    _queryId[1] = 0;
    glGenQueries(2, _queryId);
    // нужно по-разику обратиться к каждому запросу, чтобы потом не было ошибок
    glBeginQuery(GL_TIME_ELAPSED, _queryId[0]);
    glEndQuery(GL_TIME_ELAPSED);
    glBeginQuery(GL_TIME_ELAPSED, _queryId[1]);
    glEndQuery(GL_TIME_ELAPSED);
    renderTimeMsc = 0;
}

void FrameStopwatch::beginFrame() {
    _prevFrame = (_currentFrame + 1) % 2;
    glBeginQuery(GL_TIME_ELAPSED, _queryId[_currentFrame]);
}

void FrameStopwatch::endFrame() {
    glEndQuery(GL_TIME_ELAPSED);
    GLint available = 0;
    glGetQueryObjectiv(_queryId[_prevFrame], GL_QUERY_RESULT_AVAILABLE, &available); // prev frame result
    if (available) {
        GLuint64 timeElapsed = 0;
        glGetQueryObjectui64v(_queryId[_prevFrame], GL_QUERY_RESULT, &timeElapsed);
        renderTimeMsc = (int)(timeElapsed / 1000000);
    }
    _currentFrame = _prevFrame;
}
