
const unicoding = require('./build/Release/unicoding');

// UTF16 single grapheme, 2 code-point "नि"
console.log('>', unicoding.calculateUTFInfo("黄伟"));
console.log('>', unicoding.calculateUTFInfo("ḱ"));
console.log('---->', unicoding.calculateUTFInfo("𐐷"));
console.log('---->', unicoding.calculateUTFInfo("🤦"));

console.log('done');

module.exports = unicoding;
