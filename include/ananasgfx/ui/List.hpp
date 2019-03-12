#ifndef UI_LIST_H
#define UI_LIST_H

#include "Node.hpp"
#include "ListItem.hpp"
#include "Container.hpp"

namespace ui {

    class List : public Node {
    public:
        typedef struct {
            std::list<ListItem*> listItems;
            std::list<d2::Node*> dividers;
            std::optional<d2::Node*> sectionHeader;
        } SectionInfo;

        typedef std::map<std::string, SectionInfo, std::function<bool(std::string,std::string)>> SectionMap;

        typedef std::function<bool(const std::string&,const std::string&)> SectionComparator;

        List() noexcept;

        bool init() noexcept override;

        virtual d2::Node* createDivider() noexcept = 0;

        virtual densityPixel_t getDividerHeight() noexcept = 0;

        const SectionMap& getSections() const noexcept;

        std::optional<SectionInfo*> getSection(const std::string &sectionName) noexcept;

        void removeSection(const std::string &sectionName) noexcept;

        void setSectionComparator(SectionComparator sectionComparator) noexcept;

        void arrangeChildren() noexcept;

        template<class T> T* createListItem(const std::string& sectionName = "") noexcept {
            static_assert(std::is_base_of<ListItem, T>::value, "Must derive from ui::ListItem");

            // Try to create the child
            auto listItem = createChild<T>();

            // Add to section map
            this->mSectionMap[sectionName].listItems.push_back(listItem);

            // Return pointer
            return listItem;
        }

    protected:
        bool sectionComperator(const std::string& a, const std::string& b) const noexcept;

        template<class T> T* createChild() noexcept {
            return gfx::Node::createChild<T>();
        }

    private:
        /**
         * @brief Function that compares the keys of the list sections map.
         */
        SectionComparator mSectionComparator = nullptr;

        /**
         * @brief This map contains the names of the StoreSections as key and the StoreSection content as value.
         * It is sorted by the custom comparator given.
         */
        SectionMap mSectionMap;

        /**
         * @brief Defines whether or not to auto remove storesections if they are empty.
         */
        bool mAutoRemoveEmptySections = false;

        /**
         * @brief Defines whether or not to draw dividers.
         */
        bool mDrawDividers = true;

        /**
         * @brief Defines whether or not to draw the last divider.
         */
        bool mDrawLastDivider;

        //std::optional<std::tuple<ui::ListItem*,const gfx::Touch*>> mCurrentTouch;
    };

}

#endif