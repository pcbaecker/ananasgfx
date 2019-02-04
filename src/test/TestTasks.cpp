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

        // We never want to retain the task
        return false;
    }

    IfTask::IfTask(std::function<bool(gfx::Application*)> condition,
                   std::function<void(gfx::Application*)> thenDo,
                   std::function<void(gfx::Application*)> elseDo) noexcept :
            mCondition(std::move(condition)), mThenDo(std::move(thenDo)), mElseDo(std::move(elseDo)) {

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

    Compare::Compare(const std::string &nodepath, const std::string &filepath) noexcept : mNodepath(nodepath), mFilepath(filepath) {

    }

    bool Compare::offerRecreation(gfx::Application* application) noexcept {
        // Try to get the node
        auto node = application->getNode(this->mNodepath);
        if (!node.has_value()) {
            std::cerr << "### ERROR ### NODE " << this->mNodepath << " NOT FOUND" << std::endl;
            return false;
        }

        // Try to save the node to a file
        auto bitmapOpt = (*node)->asRenderTexture()->toBitmap();
        if (!bitmapOpt.has_value()) {
            std::cerr << "### ERROR ### COULD NOT CONVERT " << this->mNodepath << " TO BITMAP" << std::endl;
            return false;
        }
        if (!(*bitmapOpt)->saveAsFile("tmp.png")) {
            std::cerr << "### ERROR ### COULD NOT SAVE " << this->mNodepath << " TO FILE " << this->mFilepath << std::endl;
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
                if (!offerRecreation(application)) {
                    // TODO handle recreation unsuccessful
                }
            }
            // TODO handle template not found -> test fail
            return false;
        }

        // Try to get the node
        auto node = application->getNode(this->mNodepath);
        if (!node.has_value()) {
            // TODO handle node not found -> test fail
            return false;
        }

        // Try to render the node into a bitmap
        auto nodeBitmap = (*node)->asRenderTexture()->toBitmap();
        if (!nodeBitmap.has_value()) {
            // TODO handle error -> test fail
            return false;
        }

        // Hash the bitmaps
        auto templateHash = test::PHash::hash(*templateBitmap->get());
        auto nodeHash = test::PHash::hash(*nodeBitmap->get());

        // Compare the hashes
        std::cout << "Distance = " << (int)test::PHash::distance(templateHash, nodeHash) << std::endl;
        // TODO handle comparision to determine if test is successful or not

        return false;
    }

}