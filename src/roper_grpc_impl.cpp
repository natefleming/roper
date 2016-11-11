#include <iostream>
#include <grpc++/grpc++.h>
#include <glog/logging.h>
#include "roper.grpc.pb.h"


using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;
using grpc::Channel;
using grpc::ClientContext;

namespace moserit {

	namespace roper {

		namespace impl {

			class LandlordServiceImpl GRPC_FINAL : public moserit::roper::LandlordService::Service {

				public:

					LandlordServiceImpl();
					virtual ~LandlordServiceImpl();
				
					virtual Status Find(ServerContext* context, const FindLeasesRequest* request, FindLeasesResponse* response) override;
					virtual Status Request(ServerContext* context, const LeaseAcquireRequest* request, LeaseAcquireResponse* response) override;
					virtual Status Renew(ServerContext* context, const LeaseRenewRequest* request, LeaseRenewResponse* response) override;
					virtual Status Cancel(ServerContext* context, const LeaseCancelRequest* request, LeaseCancelResponse* response) override;
					
				private:

					class NotifyTenant {

						public:
							
							NotifyTenant(std::shared_ptr<Lease> lease) : lease_(lease) {
								std::stringstream endpoint;
								endpoint << lease->tenant().endpoint().hostname() << ":" << lease->tenant().endpoint().port();
								stub_ = TenantService::NewStub(grpc::CreateChannel(endpoint.str(), grpc::InsecureChannelCredentials()));
							}

							void Expired() {
								LeaseExpiredRequest request;
								request.mutable_lease()->CopyFrom(*lease_);
								LeaseExpiredResponse response;
								ClientContext context;
								auto status = stub_->OnExpired(&context, request, &response);
								if(!status.ok()) {
									LOG(ERROR) << status.error_code() << ": " << status.error_message() << std::endl;	
								}
							}

						private:

							std::shared_ptr<Lease> lease_;
							std::unique_ptr<TenantService::Stub> stub_;

					};

					std::vector<std::shared_ptr<Lease>> leases_;

			};

		}

	}

}
	

moserit::roper::impl::
LandlordServiceImpl::LandlordServiceImpl() {

}

moserit::roper::impl::
LandlordServiceImpl::~LandlordServiceImpl() {

}

Status 
moserit::roper::impl::
LandlordServiceImpl::
Find(ServerContext* context, const FindLeasesRequest* request, FindLeasesResponse* response) {
	const Tenant tenant(request->tenant());
	response->mutable_request()->CopyFrom(*request);	
	return Status::OK;
}

Status 
moserit::roper::impl::
LandlordServiceImpl::
Request(ServerContext* context, const LeaseAcquireRequest* request, LeaseAcquireResponse* response) {
	std::shared_ptr<Lease> lease(new Lease);
	lease->mutable_tenant()->CopyFrom(request->tenant());
	lease->mutable_expiration_policy()->CopyFrom(request->expiration_policy());
	std::unique_ptr<Resource> resource(new Resource);
	resource->set_name(request->resource_name());
	lease->mutable_resource()->CopyFrom(*resource);

	response->mutable_request()->CopyFrom(*request);	
	response->mutable_lease()->CopyFrom(*lease);
	return Status::OK;
}

Status 
moserit::roper::impl::
LandlordServiceImpl::
Renew(ServerContext* context, const LeaseRenewRequest* request, LeaseRenewResponse* response) {
	response->mutable_request()->CopyFrom(*request);	
	return Status::OK;
}

Status 
moserit::roper::impl::
LandlordServiceImpl::
Cancel(ServerContext* context, const LeaseCancelRequest* request, LeaseCancelResponse* response) {
	response->mutable_request()->CopyFrom(*request);	
	auto found = std::find_if(
		leases_.begin(), 
		leases_.end(), 
		[request](std::shared_ptr<Lease> other) {
			return other->tenant().name() == request->lease().tenant().name() && other->resource().name() == request->lease().resource().name();
		});

	if(found != leases_.end()) {
		LOG(INFO) << "Removed lease";
		NotifyTenant notify(*found);
		notify.Expired();
		leases_.erase(found);
	}
	
	return Status::OK;
}


void RunServer(const std::string& hostname, short port) {
	using namespace std;
	using namespace moserit::roper::impl;

	stringstream ss;
	ss << hostname << ":" << port;
	string endpoint(ss.str());
	LandlordServiceImpl service;

	ServerBuilder builder;

	builder.AddListeningPort(endpoint, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);

	unique_ptr<Server> server(builder.BuildAndStart());

	LOG(INFO) << "Waiting" << endl;

	server->Wait();
}


