#include <glog/logging.h>
#include "util.h"
#include "config.h"
#include "node.h"

namespace vectordb {

Node::Node()
    :meta_(Config::GetInstance().meta_path()) {
}

Node::~Node() {
}

Status
Node::Init() {
    Status s;
    if (!util::DirOK(Config::GetInstance().data_path())) {
        util::Mkdir(Config::GetInstance().data_path());
    }

    s = meta_.Init();
    assert(s.ok());

    s = engine_manager_.Init();
    assert(s.ok());

    s = grpc_server_.Init();
    assert(s.ok());

    return Status::OK();
}

Status
Node::Start() {
    Status s;
    s = grpc_server_.Start();
    assert(s.ok());
    return Status::OK();
}

Status
Node::Stop() {
    Status s;
    s = grpc_server_.Stop();
    assert(s.ok());
    return Status::OK();
}

Status
Node::OnPing(const vectordb_rpc::PingRequest* request, vectordb_rpc::PingReply* reply) {
    if (request->msg() == "ping") {
        reply->set_msg("pang");
    } else {
        reply->set_msg("no_sound");
    }
    return Status::OK();
}

Status
Node::OnInfo(const vectordb_rpc::InfoRequest* request, vectordb_rpc::InfoReply* reply) {
    reply->set_msg(meta_.ToStringPretty());
    return Status::OK();
}

} // namespace vectordb