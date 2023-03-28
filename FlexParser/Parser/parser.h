#ifndef __PARSER_H_2020_05_27__
#define __PARSER_H_2020_05_27__
#include <list>
#include <string>
#include <functional>

static const std::string g_tar_cpp	= "-cpp";
static const std::string g_tar_go	= "-go";

enum NODE_TYPE {
	NT_ROOT = 1,
	NT_OPER,
	NT_DATA
};

enum OPER_TYPE {
	OT_CREATE = 1,
	OT_WRITE,
	OT_CLOSE
};

enum DATA_TYPE {
	DT_FILE_NAME = 1,	//	�ļ���
	DT_CMD_RANGE,		//	Bit ��Χ
	DT_CMD_NAME,		//	������
	DT_CMT				//	ע��
};

struct node_t
{
	using Data		= std::string;

	NODE_TYPE			node_type;
	OPER_TYPE			oper_type;
	Data				data;
	DATA_TYPE			data_type;
	int					sid;			//	�������
	int					line;			//	�кţ���Ҫ���ڶ�λע��
	std::list<node_t*>	child;
};
//////////////////////////////////////////////////////////////////////////

struct target_output_intf
{
	virtual void output(node_t* root) = 0;
};

//	C++ �ļ����
struct cpp_output_t :
	target_output_intf
{
public:
	void output(node_t* root) override;

private:
	void i_output(node_t* node);
	std::string i_get_header(const std::string& name);

private:
	std::list<node_t*> data_nodes_;
	FILE* file_;
};

//	Golang �ļ����
struct go_output_t :
	target_output_intf
{
public:
	void output(node_t* root) override;

private:
	void i_output(node_t* node);
	std::string i_get_header(const std::string& name);

private:
	std::list<node_t*> data_nodes_;
	FILE* file_;
};
//////////////////////////////////////////////////////////////////////////

struct jf_cmd_parser_t
{
public:
	static jf_cmd_parser_t* instance();
	~jf_cmd_parser_t();

public:
	void set_target_type(const char* tar);
	void set_global_comment(const char* cmt);
	void set_single_line_comment(const char* cmt, int line);
	void set_file_name(const char* cmt);
	void set_bits(const char* cmt);
	void set_cmd_name(const char* cmt, int line, int sid);
	void output();

private:
	jf_cmd_parser_t();

private:
	node_t*				root_;
	node_t*				cur_node_;
	node_t*				parent_node_;
	node_t::Data		bits_;
	target_output_intf* output_;
};

#endif
