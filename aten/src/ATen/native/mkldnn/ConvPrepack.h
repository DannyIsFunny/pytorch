#pragma once

#include <ATen/Tensor.h>
#include <ATen/native/mkldnn/Common.h>
#include <ATen/native/mkldnn/OpContext.h>

#if AT_MKLDNN_ENABLED()

namespace at {
namespace native {
namespace mkldnn {
namespace internal {
namespace convolution {

c10::intrusive_ptr<mkldnn::ConvOpContext> createConvPrePackOpContext(
    Tensor weight,
    c10::optional<Tensor> bias,
    std::vector<int64_t> stride,
    std::vector<int64_t> padding,
    std::vector<int64_t> dilation,
    int64_t groups,
    std::vector<int64_t> input_size,
    std::string attr,
    std::vector<c10::optional<at::Scalar>> scalars,
    c10::optional<std::string> algorithm);

Tensor conv_run(
    const Tensor& input,
    const c10::intrusive_ptr<mkldnn::ConvOpContext>& op_context);

Tensor& conv_sum_run(
    const Tensor& input,
    Tensor& other,
    const c10::intrusive_ptr<mkldnn::ConvOpContext>& op_context);

ContextConv create(
    const Tensor& weight,
    const c10::optional<Tensor>& bias,
    const IntArrayRef padding,
    const IntArrayRef stride,
    const IntArrayRef dilation,
    const int64_t groups,
    const IntArrayRef input_size,
    const ideep::attr_t& attr);

Tensor run(ContextConv& context, const Tensor& input);

void run(ContextConv& context, const Tensor& input, void* output);

Tensor& sum_run(ContextConv& context, const Tensor& input, Tensor& other);

} // namespace convolution
} // namespace internal
} // namespace mkldnn
} // namespace native
} // namespace at

#endif // AT_MKLDNN_ENABLED()
