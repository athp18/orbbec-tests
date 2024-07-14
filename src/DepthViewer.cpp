#include "window.hpp"

#include "/Users/atharvp04/OrbbecSDK/include/libobsensor/hpp/Pipeline.hpp"
#include "/Users/atharvp04/OrbbecSDK/include/libobsensor/hpp/Error.hpp"
#include <chrono>
#include <iostream>

int main() {
    try {
        ob::Context ctx;
        auto devList = ctx.queryDeviceList();
        auto device = devList->getDevice(0);
        auto devInfo = device->getDeviceInfo();
        std::cout << "Device name: " << devInfo->name() << std::endl;

        ob::Pipeline pipe;
        auto depthProfiles = pipe.getStreamProfileList(OB_SENSOR_DEPTH);
        auto depthProfile = depthProfiles->getVideoStreamProfile(640, OB_HEIGHT_ANY, OB_FORMAT_Y16, 30);
        std::shared_ptr<ob::Config> config = std::make_shared<ob::Config>();
        config->enableStream(depthProfile);

        pipe.start(config);

        Window app("DepthViewer", depthProfile->width(), depthProfile->height());
        while (app) {
            auto frameSet = pipe.waitForFrames(200);
            if (frameSet == nullptr) {
                continue;
            }

            auto depthFrame = frameSet->depthFrame();
            if (depthFrame->index() % 30 == 0 && depthFrame->format() == OB_FORMAT_Y16) {
                uint32_t width = depthFrame->width();
                uint32_t height = depthFrame->height();
                float scale = depthFrame->getValueScale();
                uint16_t *data = (uint16_t *)depthFrame->data();

                float centerDistance = data[width * height / 2 + width / 2] * scale;
                std::cout << "Facing an object " << centerDistance << " mm away. " << std::endl;
            }

            app.addToRender(depthFrame);
        }

        pipe.stopRecord();
        pipe.stop();
    } catch (ob::Error &e) {
        std::cerr << "Function: " << e.getName() << "\nArgs: " << e.getArgs() << "\nMessage: " << e.getMessage() << "\nType: " << e.getExceptionType() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}
