#include <unistd.h>

#include <ananasgfx/test/TestTasks.hpp>
#include <ananasgfx/test/PHash.hpp>
#include <ananasgfx/gfx/Application.hpp>

namespace test {

    bool IfTask::run(gfx::Application* application) noexcept {
        // Check if our condition is matched
        if (this->mCondition && this->mCondition(application)) {
            // Make sure we have an thenDo() function
            if (this->mThenDo) {
                // Execute the thenDo()
                this->mThenDo(application);
            }
        } else {
            // Make sure we have an elseDo() function
            if (this->mElseDo) {
                // Execute the elseDo()
                this->mElseDo(application);
            }
        }

        // We are done, inform the waiting thread that we are done
        this->mPromise.set_value(true);

        // We never want to retain the task
        return false;
    }

    IfTask::IfTask(std::function<bool(gfx::Application*)> condition,
                   std::function<void(gfx::Application*)> thenDo,
                   std::function<void(gfx::Application*)> elseDo,
                   std::promise<bool> promise) noexcept :
            mCondition(std::move(condition)),
            mThenDo(std::move(thenDo)),
            mElseDo(std::move(elseDo)),
            mPromise(std::move(promise)) {

    }



    Task::Task(std::function<void(gfx::Application *)> task) noexcept : mTask(std::move(task)) {

    }

    bool Task::run(gfx::Application *application) noexcept {
        // Execute the task
        if (this->mTask) {
            this->mTask(application);
        }

        // We never want to retain the task
        return false;
    }

    Compare::Compare(const std::string &nodepath, const std::string &filepath, std::promise<bool> promise) noexcept :
    mNodepath(nodepath), mFilepath(filepath), mPromise(std::move(promise)) {

    }

    bool Compare::offerRecreation(gfx::Application* application) noexcept {
        // Try to get the node
        auto node = application->getNode(this->mNodepath);
        if (!node.has_value()) {
            std::cout << "### ERROR ### NODE " << this->mNodepath << " NOT FOUND" << std::endl;
            return false;
        }

        // Try to save the node to a file
        auto bitmapOpt = (*node)->asRenderTexture()->toBitmap();
        if (!bitmapOpt.has_value()) {
            std::cout << "### ERROR ### COULD NOT CONVERT " << this->mNodepath << " TO BITMAP" << std::endl;
            return false;
        }
        bitmapOpt->get()->flipVertical();
        if (!(*bitmapOpt)->saveAsFile("tmp.png")) {
            std::cout << "### ERROR ### COULD NOT SAVE " << this->mNodepath << " TO FILE " << this->mFilepath << std::endl;
            return false;
        }

        // Check if an old image already exists
        if (access(this->mFilepath.c_str(), F_OK ) != -1) {
            // Display the old image
            std::string cmd = "display -title \"The old image\" " + this->mFilepath + " &";
            system(cmd.c_str());
        }

        // Display the new image
        system("display -title \"Possible new image\" tmp.png &");

        // Ask the user if we want to keep the old image or override it with the new one
        std::cout << "Want to use the new image? (y/n):";
        std::string s;
        std::cin >> s;

        // Kill the display window
        system("killall display");

        // Evaluate the input
        if (s == "y" || s == "yes") {
            // Move the temporary image to the destination filepath
            std::string cmd = "mv tmp.png " + this->mFilepath;
            system(cmd.c_str());

            return true;
        } else {
            // We dont want to use the new image
            return false;
        }
    }

    bool Compare::run(gfx::Application* application) noexcept {
        // Try to load the template file
        auto templateBitmap = gfx::Bitmap::read(this->mFilepath);
        if (!templateBitmap.has_value()) {
            // Template file not found
            if (application->isDevmode()) {
                // In devmode we offer the user to auto create the fixture image
                if (offerRecreation(application)) {
                    this->mPromise.set_value(true);
                    return false;
                } else {
                    std::cout << "### INFO ### NEW TEMPLATE NOT ACCEPTED" << std::endl;
                    this->mPromise.set_value(false);
                    return false;
                }
            }
            std::cout << "### ERROR ### TEMPLATE " << this->mFilepath << " NOT FOUND" << std::endl;
            this->mPromise.set_value(false);
            return false;
        }

        // Try to get the node
        auto node = application->getNode(this->mNodepath);
        if (!node.has_value()) {
            std::cout << "### ERROR ### NODE " << this->mNodepath << " NOT FOUND" << std::endl;
            this->mPromise.set_value(false);
            return false;
        }

        // Try to render the node into a bitmap
        auto nodeBitmap = (*node)->asRenderTexture()->toBitmap();
        if (!nodeBitmap.has_value()) {
            std::cout << "### ERROR ### NODE " << this->mNodepath << " TO BITMAP FAILED" << std::endl;
            this->mPromise.set_value(false);
            return false;
        }
        nodeBitmap->get()->flipVertical();

        // Hash the bitmaps
        auto templateHash = test::PHash::hash(*templateBitmap->get());
        auto nodeHash = test::PHash::hash(*nodeBitmap->get());

        // Compare the hashes
        auto diff = test::PHash::distance(templateHash, nodeHash);
        if (diff > 0) {
            if (application->isDevmode()) {
                // In devmode we offer the user to auto create the fixture image
                if (offerRecreation(application)) {
                    this->mPromise.set_value(true);
                    return false;
                } else {
                    std::cout << "### INFO ### NEW TEMPLATE NOT ACCEPTED" << std::endl;
                    this->mPromise.set_value(false);
                    return false;
                }
            }
            std::cout << "### ERROR ### NODE " << this->mNodepath << " AND TEMPLATE " << this->mFilepath
            << " HAVE DIFFERENCE = " << (int)diff << std::endl;
            this->mPromise.set_value(false);
        } else {
            this->mPromise.set_value(true);
        }
        return false;
    }

}