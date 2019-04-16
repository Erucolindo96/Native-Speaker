#include "LearningPerformer.hpp"

LearningPerformer::LearningPerformer(const LearningPerformer &other):LearningPerformer()
{
  throw std::runtime_error("TODO");
}

LearningPerformer& LearningPerformer::operator=(const LearningPerformer &other)
{
    throw std::runtime_error("TODO");
}

LearningPerformer::LearningPerformer(LearningPerformer &&other):LearningPerformer()
{
    throw std::runtime_error("TODO");
}

LearningPerformer& LearningPerformer::operator=(LearningPerformer &&other)
{
    throw std::runtime_error("TODO");
}

const LearningThread& LearningPerformer::startLearning(std::unique_ptr<GmmModel> &m,
                                    std::unique_ptr<LearningAlgo> &&algo,
                                    std::vector<alize::Feature> &f_vec,
                                    uint32_t iter_cnt )
{
    throw std::runtime_error("TODO");
}
