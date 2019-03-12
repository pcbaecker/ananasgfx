#include <ananasgfx/ui/List.hpp>
#include <ee/Log.hpp>

namespace ui {

    List::List() noexcept :
    mSectionMap(std::bind(&List::sectionComperator, this, std::placeholders::_1, std::placeholders::_2)){

    }

    bool List::init() noexcept {
        this->arrangeChildren();
        return Node::init();
    }

    void List::setSectionComparator(List::SectionComparator sectionComparator) noexcept {
        this->mSectionComparator = std::move(sectionComparator);
    }

    const List::SectionMap &List::getSections() const noexcept {
        return this->mSectionMap;
    }

    std::optional<List::SectionInfo *> List::getSection(const std::string &sectionName) noexcept {
        if (this->mSectionMap.count(sectionName)) {
            return &this->mSectionMap.at(sectionName);
        } else {
            return std::nullopt;
        }
    }

    bool List::sectionComperator(const std::string &a, const std::string &b) const noexcept {
        // Check if a custom comparator method is present
        if (this->mSectionComparator) {
            // Execute the custom comparator
            return this->mSectionComparator(a, b);
        } else {
            // No custom comparator is present, we use the default one
            return a.compare(b) < 0;
        }
    }

    void List::removeSection(const std::string &sectionName) noexcept {
        // find section
        SectionInfo *pSection = nullptr;
        for (auto it = this->mSectionMap.begin();
             it != this->mSectionMap.end(); it++) {
            if ((*it).first == sectionName) {
                pSection = &(*it).second;
                break;
            }
        }
        if (!pSection) {
            // not found
            return;
        }
/*
        // Remove all list items
        for (std::list<ListItem *>::iterator it = pSection->listItems.begin();
             it != pSection->listItems.end(); it++) {
            gfx::Node2d::removeChild(*it);
        }

        // Remove all dividers
        for (std::list<Node2d *>::iterator it = pSection->dividers.begin(); it != pSection->dividers.end(); it++) {
            gfx::Node2d::removeChild(*it);
        }

        // Remove section divider
        if (pSection->pSectionHeader) {
            gfx::Node2d::removeChild(pSection->pSectionHeader);
        }

        // remove section
        this->mListSections.erase(sectionName);

        // update
        this->updateChildrenRect();*/
    }

    void List::arrangeChildren() noexcept {
        // Auto remove empty sections
        if (this->mAutoRemoveEmptySections) {
            std::list<std::string> sectionsToDelete;
            for (auto &section : this->mSectionMap) {
                if (!section.first.empty() && section.second.listItems.empty()) {
                    sectionsToDelete.push_back(section.first);
                }
            }

            for (auto &s : sectionsToDelete) {
                this->removeSection(s);
            }
        }

        // get heighest position to position the items from up till down
        float y = 0.0f;

        // Iterate through the sections
        bool noRows = true;
        for (auto& section : this->mSectionMap) {
            if (this->mDrawDividers) {
                size_t requiredDivs = section.second.listItems.size();

                // If we should not draw the last divider, remove one div
                if (!this->mDrawLastDivider && requiredDivs > 0)
                    requiredDivs--;

                // Check if we have to remove some dividers
                while (section.second.dividers.size() > requiredDivs) {
                    //gfx::Node2d::removeChild((*it).second.dividers.back());
                    //(*it).second.dividers.pop_back();
                }

                // Check if we have to add some dividers
                while (section.second.dividers.size() < requiredDivs) {
                    auto divider = this->createDivider();
                    divider->setSize(this->mSize.x, toVerticalPixel(getDividerHeight()));
                    //pDivider->setAnchorPoint(gfx::Point2D(0, 1));
                    section.second.dividers.push_back(divider);
                    //gfx::Node2d::addChild(pDivider);
                }
            }

            // Section headers
            if (section.first != "") {/*
                // Create
                if (!(*it).second.pSectionHeader) {
                    (*it).second.pSectionHeader = this->design_getSectionHeader((*it).first);
                    (*it).second.pSectionHeader->setAnchorPoint(gfx::Point2D(0, 1));
                    (*it).second.pSectionHeader->setSize(
                            gfx::Size2d(this->mRect.size.width, this->design_getSectionHeaderHeight()));
                    this->addChild((*it).second.pSectionHeader);
                }

                // set position
                (*it).second.pSectionHeader->setPosition(gfx::Point2D(0, y));
                y -= (*it).second.pSectionHeader->getRect().size.height;*/
            }

            // Iterate through all list items from this section and their dividers
            auto divIt = section.second.dividers.begin();
            for (auto& listItem : section.second.listItems) {
                // Check if we have enough space
                if (y >= this->mSize.y) {
                    listItem->setVisible(false);
                    WARN("There is not enough vertical space for all items", {});
                    continue;
                }

                // Position list item
                //(*jt)->setAnchorPoint(gfx::Point2D(0, 1));
                listItem->setSize(this->mSize.x, toVerticalPixel(listItem->getHeight()));
                listItem->setPosition(0.0f, y);
                listItem->setAnchorPoint(0.0f, 0.0f);
                y += listItem->getSize().y;

                // position corresponding divider
                if (this->mDrawDividers && divIt != section.second.dividers.end()) {
                    (*divIt)->setPosition(0.0f, y);
                    y += (*divIt)->getSize().y;
                    divIt++;
                }
            }
        }
/*
        // If there are no rows display no rows label
        if (this->pNoContentLabel) {
            if (this->mListSections.empty()) {
                this->pNoContentLabel->setVisible(true);
            } else  {
                this->pNoContentLabel->setVisible(false);
            }
        }*/
    }
}