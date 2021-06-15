#ifndef __VECTORDB_VCLIENT_H__
#define __VECTORDB_VCLIENT_H__

#include <memory>
#include <glog/logging.h>
#include <grpcpp/grpcpp.h>
#include "vectordb_rpc.grpc.pb.h"
#include "status.h"

namespace vectordb {

class VClient {
  public:
    static VClient&
    GetInstance() {
        static VClient instance;
        return instance;
    }

    VClient(const VClient&) = delete;
    VClient& operator=(const VClient&) = delete;

    Status Init();
    Status Start();
    Status Stop();

  private:
    VClient();
    ~VClient();

    void Prompt() const;
    void ShowReply(const std::string &s) const;
    void Do(const std::vector<std::string> &cmd_sv, const std::string &params_json);

    void Ping(const vectordb_rpc::PingRequest &request, std::string &reply_msg);
    void Info(const vectordb_rpc::InfoRequest &request, std::string &reply_msg);
    void CreateTable(const vectordb_rpc::CreateTableRequest &request, std::string &reply_msg);
    void ShowTables(const vectordb_rpc::ShowTablesRequest &request, std::string &reply_msg);
    void Describe(const vectordb_rpc::DescribeRequest &request, std::string &reply_msg);
    void PutVec(const vectordb_rpc::PutVecRequest &request, std::string &reply_msg);
    void GetVec(const vectordb_rpc::GetVecRequest &request, std::string &reply_msg);
    void DistKey(const vectordb_rpc::DistKeyRequest &request, std::string &reply_msg);
    void Keys(const vectordb_rpc::KeysRequest &request, std::string &reply_msg);
    void BuildIndex(const vectordb_rpc::BuildIndexRequest &request, std::string &reply_msg);
    void GetKNN(const vectordb_rpc::GetKNNRequest &request, std::string &reply_msg);

    std::shared_ptr<grpc::Channel> channel_;
    std::unique_ptr<vectordb_rpc::VectorDB::Stub> stub_;
};

} // namespace vectordb

#endif
