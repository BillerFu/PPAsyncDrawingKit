//
//  PPImage.m
//  PPAsyncDrawingKit
//
//  Created by DSKcpp on 2016/12/25.
//  Copyright © 2016年 DSKcpp. All rights reserved.
//

#import "PPImage.h"
#import "NSData+PPImageContentType.h"
#import "PPImage+WebP.h"

@implementation PPImage
+ (UIImage *)imageWithData:(NSData *)data
{
    UIImage *image;
    PPImageFormat imageFormat = [NSData pp_imageFormatForImageData:data];
    if (imageFormat == PPImageFormatGIF) {
        image = [PPImage animatedGIFWithData:data];
    } else if (imageFormat == PPImageFormatWebP) {
#if __has_include(<WebP/decode.h>)
        image = [PPImage imageWithWebPData:data];
#endif
    } else {
        image = [UIImage imageWithData:data];
    }
    NSLog(@"%zd", image.images.count);
    return image;
}

+ (UIImage *)imageWithContentsOfFile:(NSString *)path
{
    NSData *data = [NSData dataWithContentsOfFile:path];
    return [self imageWithData:data];
}

+ (UIImage *)animatedGIFWithData:(NSData *)data
{
    if (!data) {
        return nil;
    }
    
    CGImageSourceRef source = CGImageSourceCreateWithData((__bridge CFDataRef)data, NULL);
    
    size_t count = CGImageSourceGetCount(source);
    
    UIImage *staticImage;
    
    if (count <= 1) {
        staticImage = [[UIImage alloc] initWithData:data];
    } else {
        CGFloat scale = 1;
        scale = [UIScreen mainScreen].scale;
        
        NSMutableArray *images = @[].mutableCopy;
        for (NSInteger i = 0; i < count; i++) {
            CGImageRef CGImage = CGImageSourceCreateImageAtIndex(source, i, NULL);
            UIImage *frameImage = [UIImage imageWithCGImage:CGImage scale:scale orientation:UIImageOrientationUp];
            [images addObject:frameImage];
            CGImageRelease(CGImage);
        }
        staticImage = [UIImage animatedImageWithImages:images duration:0.0f];
    }
    
    CFRelease(source);
    
    return staticImage;
}

- (BOOL)isGIF
{
    return (self.images != nil);
}
@end
