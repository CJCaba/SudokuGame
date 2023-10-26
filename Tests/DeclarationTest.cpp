/**
 * @file DeclarationTest.cpp
 * @author jadec
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Declaration.h>
#include <DeclarationNumber.h>
#include <DeclarationGiven.h>
#include <DeclarationInteract.h>
#include <DeclarationSparty.h>
#include <DeclarationContainer.h>

TEST(DeclarationTest, Construct){
    DeclarationGiven decGiv(nullptr);
    DeclarationInteract decInt(nullptr);
    DeclarationSparty decSpar(nullptr);
    DeclarationContainer decCon(nullptr);
}

TEST(DeclarationTest, GettersSetters){
    DeclarationGiven decGiv(nullptr);

    decGiv.SetValue(6);
    ASSERT_EQ(decGiv.GetValue(), 6);
    decGiv.SetSize(48, 96);
    ASSERT_EQ(decGiv.GetWidth(), 48);
    ASSERT_EQ(decGiv.GetHeight(), 96);
    std::wstring image;
//    decGiv.SetImage(image);
//    ASSERT_EQ(decGiv.GetImage(), );

}