#pragma once

#include "layer.h"

namespace cheap {



	class layer_manager
	{
	public:
		class level
		{
		public:
			level* mAbove;
			level* mBelow;
			layer* mLayer;

			explicit level(graphics_entity* aGraphics_entity)
				:
				mAbove(nullptr),
				mBelow(nullptr),
				mLayer(new layer(aGraphics_entity))
			{
				LOG();
			}

			level()
				:
				mAbove(nullptr),
				mBelow(nullptr),
				mLayer(nullptr)
			{
				LOG();
			}

			~level()
			{
				LOG();
				delete mLayer;
			}

			// but will NOT delete level itself
			void remove_and_delete_layer()
			{
				if (mAbove != nullptr)
					mAbove->mBelow = mBelow;

				if (mBelow != nullptr)
					mBelow->mAbove = mAbove;

				delete mLayer;
			}
			// but will NOT delete level itself
			void remove()
			{
				if (mAbove != nullptr)
					mAbove->mBelow = mBelow;

				if (mBelow != nullptr)
					mBelow->mAbove = mAbove;
			}
		};

		layer_manager()
			:
			mHash_id_to_layer(std::unordered_map<unsigned int, level*>()),
			mList_dummy_head(level())
		{
			LOG();
		}

		layer_manager(const layer_manager& aLayer_manager) = delete;
		layer_manager& operator=(const layer_manager& aLayer_manager) = delete;
		layer_manager(const layer_manager&& aLayer_manager) noexcept = delete;

		~layer_manager()
		{
			LOG();
			for (const level* current = mList_dummy_head.mBelow; current != nullptr; ) {
				const level* below = current->mBelow;
				delete current;
				current = below;
			}
		}

		layer* get_layer(unsigned int aGraphics_entity_id)
		{
			if (mHash_id_to_layer.contains(aGraphics_entity_id)) {
				return mHash_id_to_layer[aGraphics_entity_id]->mLayer;
			}
			return nullptr;
		}

		[[nodiscard]] level* get_top_layer_level() const
		{
			//LOG();
			return mList_dummy_head.mBelow;
		}

		// add layer top
		void add_layer(graphics_entity* aGraphics_entity)
		{
			LOG();
			const auto lvl = new level(aGraphics_entity);
			add(lvl);
		}

		void add_anime(
			const unsigned int aGraphics_entity_id,
			animation* aAnimation)
		{
			if (mHash_id_to_layer.contains(aGraphics_entity_id)) {
				mHash_id_to_layer[aGraphics_entity_id]->mLayer->set_anim(aAnimation);
			} else {
				LOG_INFO("操你妈，你给的这个animation对应的graphics_entity的id不在layer_manager里面，怎么回事，是layer_manager错了还是哪里");
			}
		}

		void add_layer_above(
			const unsigned int aTarget_id,
			graphics_entity* aGraphics_entity)
		{
			LOG();
			const auto lvl = new level(aGraphics_entity);

			if (mHash_id_to_layer.contains(aTarget_id))
				add_above(mHash_id_to_layer[aTarget_id], lvl);
			else
				add(lvl);
		}


		void add_layer_below(
			const unsigned int aTarget_id,
			graphics_entity* aGraphics_entity)
		{
			LOG();
			const auto lvl = new level(aGraphics_entity);

			if (mHash_id_to_layer.contains(aTarget_id))
				add_below(mHash_id_to_layer[aTarget_id], lvl);
			else
				add(lvl);
		}

		// TODO
		void update_layer(const unsigned int aId)
		{
			LOG();
			if (mHash_id_to_layer.contains(aId))
				mHash_id_to_layer[aId]->mLayer->update();
		}

		// TODO
		void remove_and_delete_layer(const unsigned int aGraphics_entity_id)
		{
			if (mHash_id_to_layer.contains(aGraphics_entity_id)) {
				level* to_remove = mHash_id_to_layer[aGraphics_entity_id];
				to_remove->remove();
				delete to_remove;
				mHash_id_to_layer.erase(aGraphics_entity_id);
			}
		}

	private:

		std::unordered_map<unsigned int, level*> mHash_id_to_layer;
		level mList_dummy_head;

		static void insert_above(level* aLevel, level* aNew)
		{
			LOG();
			aNew->mBelow = aLevel;
			aNew->mAbove = aLevel->mAbove;

			if (aLevel->mAbove != nullptr)
				aLevel->mAbove->mBelow = aNew;
			aLevel->mAbove = aNew;

		}

		static void insert_below(level* aLevel, level* aNew)
		{
			LOG();
			aNew->mAbove = aLevel;
			aNew->mBelow = aLevel->mBelow;

			if (aLevel->mBelow != nullptr)
				aLevel->mBelow->mAbove = aNew;
			aLevel->mBelow = aNew;
		}

		// add layer top
		void add(level* aLvl)
		{
			LOG();
			insert_below(&mList_dummy_head, aLvl);
			mHash_id_to_layer[aLvl->mLayer->get_id()] = aLvl;
		}

		void add_above(level* aTarget,
			level* aLvl)
		{
			LOG();
			insert_above(aTarget, aLvl);
			mHash_id_to_layer[aLvl->mLayer->get_id()] = aLvl;
		}
		void add_below(level* aTarget,
			level* aLvl)
		{
			LOG();
			insert_below(aTarget, aLvl);
			mHash_id_to_layer[aLvl->mLayer->get_id()] = aLvl;
		}
	};
}
