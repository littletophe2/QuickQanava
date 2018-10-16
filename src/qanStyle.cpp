/*
 Copyright (c) 2008-2018, Benoit AUTHEMAN All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the author or Destrat.io nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL AUTHOR BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

//-----------------------------------------------------------------------------
// This file is a part of the QuickQanava software library.
//
// \file	qanStyle.cpp
// \author	benoit@destrat.io
// \date	2015 06 05
//-----------------------------------------------------------------------------

// Qt headers
#include <QFont>

// QuickQanava headers
#include "./qanStyle.h"
#include "./qanGraph.h"

namespace qan { // ::qan

/* Style Object Management *///------------------------------------------------
Style::Style( QString name, QObject* parent ) :
    QObject{ parent },
    _name{ name }
{

}
//-----------------------------------------------------------------------------

/* Node Style Object Management *///-------------------------------------------
NodeStyle::NodeStyle( QString name, QObject* parent ) :
    qan::Style( name, parent )
{
}
//-----------------------------------------------------------------------------

/* Node Style Properties *///--------------------------------------------------
void    NodeStyle::setBackRadius( qreal backRadius ) noexcept
{
    // PRECONDITIONS:
        // backRadius must be >= 0.
    if ( backRadius < -0.00001 ) {
        qWarning() << "qan::NodeStyle::setBackRadius(): Node background radius can't be < 0.";
        return;
    }
    if ( !qFuzzyCompare( 1. + _backRadius, 1. + backRadius ) ) {
        _backRadius = backRadius;
        Q_EMIT backRadiusChanged();
    }
}

void    NodeStyle::setBackOpacity( qreal backOpacity ) noexcept
{
    if ( !qFuzzyCompare( 1. + _backOpacity, 1. + backOpacity ) ) {
        _backOpacity = backOpacity;
        Q_EMIT backOpacityChanged();
    }
}

void    NodeStyle::setFillType(NodeStyle::FillType fillType) noexcept
{
    if ( _fillType != fillType ) {
        _fillType = fillType;
        Q_EMIT fillTypeChanged();
    }
}

void    NodeStyle::setBackColor( const QColor& backColor ) noexcept
{
    if ( _backColor != backColor ) {
        _backColor = backColor;
        Q_EMIT backColorChanged();
    }
}

void    NodeStyle::setBaseColor( const QColor& baseColor ) noexcept
{
    if ( _baseColor != baseColor ) {
        _baseColor = baseColor;
        Q_EMIT baseColorChanged();
    }
}

void    NodeStyle::setBorderColor( const QColor& borderColor ) noexcept
{
    if ( _borderColor != borderColor ) {
        _borderColor = borderColor;
        Q_EMIT borderColorChanged();
    }
}

void    NodeStyle::setBorderWidth( qreal borderWidth ) noexcept
{
    if ( !qFuzzyCompare( 1. + _borderWidth, 1. + borderWidth ) ) {
        _borderWidth = borderWidth;
        Q_EMIT borderWidthChanged();
    }
}

void    NodeStyle::setEffectType(NodeStyle::EffectType effectType) noexcept
{
    if ( _effectType != effectType ) {
        setEffectEnabled(effectType == EffectType::EffectNone ? false : true);
        _effectType = effectType;
        Q_EMIT effectTypeChanged();
    }
}

void    NodeStyle::setEffectEnabled(bool effectEnabled) noexcept
{
    if ( _effectEnabled != effectEnabled ) {
        _effectEnabled = effectEnabled;
        Q_EMIT effectEnabledChanged();
    }
}

void    NodeStyle::setEffectColor(QColor effectColor) noexcept
{
    if ( _effectColor != effectColor ) {
        _effectColor = effectColor;
        Q_EMIT effectColorChanged();
    }
}

void    NodeStyle::setEffectRadius( qreal effectRadius ) noexcept
{
    if (effectRadius < 0.0)
            return;
    if ( !qFuzzyCompare( 1. + _effectRadius, 1. + effectRadius ) ) {
        _effectRadius = effectRadius;
        Q_EMIT effectRadiusChanged();
    }
}

void    NodeStyle::setEffectOffset( qreal effectOffset ) noexcept
{
    if ( !qFuzzyCompare( 1. + _effectOffset, 1. + effectOffset ) ) {
        _effectOffset = effectOffset;
        Q_EMIT effectOffsetChanged();
    }
}

void    NodeStyle::setFontPointSize( int fontPointSize ) noexcept
{
    if ( _fontPointSize != fontPointSize ) {
        _fontPointSize = fontPointSize;
        Q_EMIT fontPointSizeChanged();
    }
}

void    NodeStyle::setFontBold( bool fontBold ) noexcept
{
    if ( _fontBold != fontBold ) {
        _fontBold = fontBold;
        Q_EMIT fontBoldChanged();
    }
}
//-----------------------------------------------------------------------------


/* Edge Style Object Management *///-------------------------------------------
EdgeStyle::EdgeStyle( QString name, QObject* parent ) :
    qan::Style( name, parent )
{
}

void    EdgeStyle::setLineType( LineType lineType ) noexcept
{
    if ( lineType != _lineType ) {
        _lineType = lineType;
        Q_EMIT lineTypeChanged();
        Q_EMIT styleModified();
    }
}

void    EdgeStyle::setLineColor( const QColor& lineColor ) noexcept
{
    if ( lineColor != _lineColor ) {
        _lineColor = lineColor;
        Q_EMIT lineColorChanged();
        Q_EMIT styleModified();
    }
}

void    EdgeStyle::setLineWidth( qreal lineWidth ) noexcept
{
    if ( !qFuzzyCompare( 1.0 + lineWidth, 1.0 + _lineWidth ) ) {
        _lineWidth = lineWidth;
        Q_EMIT lineWidthChanged();
        Q_EMIT styleModified();
    }
}

void    EdgeStyle::setArrowSize( qreal arrowSize ) noexcept
{
    if ( !qFuzzyCompare(1. + arrowSize, 1. + _arrowSize ) ) {
        _arrowSize = arrowSize;
        Q_EMIT arrowSizeChanged();
        Q_EMIT styleModified();
    }
}

auto    EdgeStyle::setSrcShape(ArrowShape srcShape) noexcept -> void
{
    if ( _srcShape != srcShape ) {
        _srcShape = srcShape;
        Q_EMIT srcShapeChanged();
        Q_EMIT styleModified();
    }
}

auto    EdgeStyle::setDstShape(ArrowShape dstShape) noexcept -> void
{
    if ( _dstShape != dstShape ) {
        _dstShape = dstShape;
        Q_EMIT dstShapeChanged();
        Q_EMIT styleModified();
    }
}

void    EdgeStyle::setDashed( bool dashed ) noexcept
{
    if ( dashed != _dashed ) {
        _dashed = dashed;
        Q_EMIT dashedChanged();
    }
}

void    EdgeStyle::setDashPattern( const QVector<qreal>& dashPattern ) noexcept
{
    _dashPattern = dashPattern;
    Q_EMIT dashPatternChanged();
}

const QVector<qreal>& EdgeStyle::getDashPattern() const noexcept { return _dashPattern; }
//-----------------------------------------------------------------------------

} // ::qan

