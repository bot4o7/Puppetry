#pragma once

namespace cheap {


	// gfx entity num;
	struct gfx_entity_param
	{
		unsigned int mId;
		float mX;
		float mY;
		float mZ;
		float mHeight;
		std::string mPic_file_path;
		bool mIs_RGBA;
		bool mIs_receive_mouse;
	};
	// page id
	struct page_param
	{
		unsigned int id;
		unsigned int graphics_entity_num;
		gfx_entity_param** param_list;
		unsigned int next_id;
		std::string next_file_path;

		page_param(unsigned aId, unsigned aNum)
			:id(aId), graphics_entity_num(aNum), param_list(new gfx_entity_param* [graphics_entity_num]), next_id(0), next_file_path("")
		{
			LOG();
		}
		~page_param()
		{
			LOG();
			for (int i = 0; i < graphics_entity_num; ++i) {
				delete param_list[i];
			}
			delete[] param_list;
		}

	};

	static page_param* load_init_page(const std::string& file_path)
	{
		LOG();
		static const unsigned size = 512;
		//LOG_INFO("file path : " << file_path);
		std::ifstream f(file_path.c_str());
		char bufLine[size];
		f.getline(bufLine, size); //读取一行
		unsigned id = std::stoi(bufLine);
		LOG_INFO(bufLine);
		f.getline(bufLine, size); //读取一行
		unsigned num = std::stoi(bufLine);
		LOG_INFO(bufLine);

		page_param* pp = new page_param(id, num);
		pp->id = id;
		pp->graphics_entity_num = num;

		for (int i = 0; i < num; ++i) {
			pp->param_list[i] = new gfx_entity_param();
			f.getline(bufLine, size); //读取一行
			pp->param_list[i]->mId = std::stoi(bufLine);
			LOG_INFO(bufLine);
			f.getline(bufLine, size); //读取一行
			pp->param_list[i]->mX = std::stof(bufLine);
			LOG_INFO(bufLine);
			f.getline(bufLine, size); //读取一行
			pp->param_list[i]->mY = std::stof(bufLine);
			LOG_INFO(bufLine);
			f.getline(bufLine, size); //读取一行
			pp->param_list[i]->mZ = std::stof(bufLine);
			LOG_INFO(bufLine);
			f.getline(bufLine, size); //读取一行
			pp->param_list[i]->mHeight = std::stof(bufLine);
			LOG_INFO(bufLine);
			f.getline(bufLine, size); //读取一行
			//pp->param_list[i]->mPic_file_path = std::string(bufLine);
			pp->param_list[i]->mPic_file_path = bufLine;
			LOG_INFO(bufLine);
			f.getline(bufLine, size); //读取一行
			pp->param_list[i]->mIs_RGBA = (std::stoi(bufLine) == 1);
			LOG_INFO(bufLine);
			f.getline(bufLine, size); //读取一行
			pp->param_list[i]->mIs_receive_mouse = (std::stoi(bufLine) == 1);
			LOG_INFO(bufLine);
		}

		f.getline(bufLine, size); //读取一行
		pp->next_id = std::stoi(bufLine);
		LOG_INFO(bufLine);
		f.getline(bufLine, size); //读取一行
		pp->next_file_path = bufLine;
		LOG_INFO(bufLine);

		f.close();

		return pp;
	}


	class visual_novel
	{
	public:
		struct scene
		{
			unsigned int mId;
			std::string mFile_path;
			page_param* mPage_param; // 有选择分支时，不同选择分支可能会更改这个值
			scene(unsigned           id,
				const std::string& file_path) :mId(id), mFile_path(file_path), mPage_param(load_init_page(file_path))
			{
				LOG();
			}
			~scene()
			{
				LOG();
				delete mPage_param;
			}
		};

		scene mCurrent;

		visual_novel(unsigned           id,
			const std::string& file_path) :
			mCurrent(id, file_path),
			mIs_ready_to_page(false)
		{
			LOG();
		}


		page_param* next_page()
		{
			LOG();
			mCurrent.mId = mCurrent.mPage_param->next_id;
			mCurrent.mFile_path = mCurrent.mPage_param->next_file_path;
			mCurrent.mPage_param = load_init_page(mCurrent.mFile_path);

			return mCurrent.mPage_param;
		}

		// TODO
		bool is_ready_to_page()
		{
			return mIs_ready_to_page;
		}

		void update_is_ready_to_page(int aId)
		{
			LOG();
			mIs_ready_to_page = true;
			if (aId > -1) {
				mCurrent.mId = aId;
				mCurrent.mPage_param->next_file_path = mCurrent.mPage_param->next_file_path.substr(0, 1 + mCurrent.mPage_param->next_file_path.find_last_of('/'));
				mCurrent.mPage_param->next_file_path.append(std::to_string(aId));
				LOG_INFO("update file path : " << mCurrent.mPage_param->next_file_path);
			}
		}
		void reset_is_ready_to_page()
		{
			LOG();
			mIs_ready_to_page = false;
		}
	private:
		bool mIs_ready_to_page;
	};

}