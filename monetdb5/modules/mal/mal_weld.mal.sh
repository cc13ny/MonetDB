# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0.  If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# Copyright 1997 - July 2008 CWI, August 2008 - 2018 MonetDB B.V.

sed '/^$/q' $0			# copy copyright from this file

cat <<EOF
# This file was generated by using the script ${0##*/}.

module weld;

EOF

integer=(bte int lng)	# all integer types
numeric=(${integer[@]} flt dbl)	# all numeric types
alltypes=(bit ${numeric[@]} oid str)

cat <<EOF

pattern initstate():ptr
address WeldInitState
comment "Initialize the state structure that is used to build a weld program";

pattern run(wstate:ptr, arg:any...):any...
address WeldRun
comment "Compile and run the Weld program";

pattern algebraprojection(left:bat[:oid], right:bat[:any_1], wstate:ptr):bat[any_1]
address WeldAlgebraProjection
comment "algebra.projection";

pattern algebraselect(b:bat[:any_1], low:any_1, high:any_1, li:bit, hi:bit, anti:bit, wstate:ptr):bat[:oid]
address WeldAlgebraSelect1
comment "algebra.select";

pattern algebraselect(b:bat[:any_1], s:bat[:oid], low:any_1, high:any_1, li:bit, hi:bit, anti:bit, wstate:ptr):bat[:oid]
address WeldAlgebraSelect2
comment "algebra.select";

pattern algebrathetaselect(b:bat[:any_1], val:any_1, op:str, wstate:ptr):bat[:oid]
address WeldAlgebraThetaselect1
comment "algebra.thetaselect";

pattern algebrathetaselect(b:bat[:any_1], s:bat[:oid], val:any_1, op:str, wstate:ptr):bat[:oid]
address WeldAlgebraThetaselect2
comment "algebra.thetaselect";

pattern groupgroup(b:bat[:any_1], wstate:ptr) (groups:bat[:oid], extents:bat[:oid], histo:bat[:lng])
address WeldGroup
comment "group.group";

pattern groupgroup(b:bat[:any_1], g:bat[:oid], wstate:ptr) (groups:bat[:oid], extents:bat[:oid], histo:bat[:lng])
address WeldGroup
comment "group.groupdone";

pattern aggrsubsum(b:bat[:any_1], g:bat[:oid], e:bat[:any_2], skip_nils:bit, abort_on_error:bit, wstate:ptr):bat[:any_3]
address WeldAggrSubSum
comment "aggr.subsum";
pattern aggrsubsum(b:bat[:any_1], g:bat[:oid], e:bat[:any_2], s:bat[:oid], skip_nils:bit, abort_on_error:bit, wstate:ptr):bat[:any_3]
address WeldAggrSubSum
comment "aggr.subsum";

pattern aggrsubprod(b:bat[:any_1], g:bat[:oid], e:bat[:any_2], skip_nils:bit, abort_on_error:bit, wstate:ptr):bat[:any_1]
address WeldAggrSubProd
comment "aggr.subprod";

pattern aggrsubprod(b:bat[:any_1], g:bat[:oid], e:bat[:any_2], s:bat[:oid], skip_nils:bit, abort_on_error:bit, wstate:ptr):bat[:any_1]
address WeldAggrSubProd
comment "aggr.subprod";

pattern aggrsubmin(b:bat[:any_1], g:bat[:oid], e:bat[:any_2], skip_nils:bit, wstate:ptr):bat[:any_1]
address WeldAggrSubMin
comment "aggr.submin";

pattern aggrsubmin(b:bat[:any_1], g:bat[:oid], e:bat[:any_2], s:bat[:oid], skip_nils:bit, wstate:ptr):bat[:any_1]
address WeldAggrSubMin
comment "aggr.submin";

pattern aggrsubmax(b:bat[:any_1], g:bat[:oid], e:bat[:any_2], skip_nils:bit, wstate:ptr):bat[:any_1]
address WeldAggrSubMax
comment "aggr.submax";

pattern aggrsubmax(b:bat[:any_1], g:bat[:oid], e:bat[:any_2], s:bat[:oid], skip_nils:bit, wstate:ptr):bat[:any_1]
address WeldAggrSubMax
comment "aggr.submax";

pattern aggrsubcount(b:bat[:any_1], g:bat[:oid], e:bat[:any_2], skip_nils:bit, wstate:ptr):bat[:lng]
address WeldAggrSubCount
comment "aggr.subcount";

pattern aggrsubcount(b:bat[:any_1], g:bat[:oid], e:bat[:any_2], s:bat[:oid], skip_nils:bit, wstate:ptr):bat[:lng]
address WeldAggrSubCount
comment "aggr.subcount";

pattern sqlprojectdelta(select:bat[:oid], col:bat[:any_3], uid:bat[:oid], uval:bat[:any_3], wstate:ptr):bat[:any_3]
address WeldSqlProjectDelta
comment "sql.projectdelta";

pattern sqlprojectdelta(select:bat[:oid], col:bat[:any_3], uid:bat[:oid], uval:bat[:any_3], ins:bat[:any_3], wstate:ptr):bat[:any_3]
address WeldSqlProjectDelta
comment "sql.projectdelta";

pattern batmtimeyear(d:bat[:date], wstate:ptr):bat[:int]
address WeldBatMtimeYear
comment "batmtime.year";

pattern batmergecand(a:bat[:oid], b:bat[:oid], wstate:ptr):bat[:oid]
address WeldBatMergeCand
comment "bat.mergecand";

pattern batmirror(b:bat[:any_2], wstate:ptr):bat[:oid]
address WeldBatMirror
comment "bat.mirror";

pattern batcalcidentity(b:bat[:any_2], wstate:ptr):bat[:oid] 
address WeldBatcalcIdentity
comment "batcalc.identity";

pattern algebrajoin(l:bat[:any_1], r:bat[:any_1], sl:bat[:oid], sr:bat[:oid], nil_matches:bit, estimate:lng, wstate:ptr) (X_0:bat[:oid], X_1:bat[:oid])
address WeldAlgebraJoin
comment "algebra.join"

pattern algebradifference(l:bat[:any_1], r:bat[:any_1], sl:bat[:oid], sr:bat[:oid], nil_matches:bit, estimate:lng, wstate:ptr):bat[:oid]
address WeldAlgebraDifference
comment "algebra.difference";

pattern algebraintersect(l:bat[:any_1], r:bat[:any_1], sl:bat[:oid], sr:bat[:oid], nil_matches:bit, estimate:lng, wstate:ptr):bat[:oid]
address WeldAlgebraIntersect
comment "algebra.intersect";

EOF

for tp in ${numeric[@]}; do
    cat <<EOF
pattern aggrsum(b:bat[:$tp], wstate:ptr):$tp
address WeldAggrSum
comment "aggr.sum";
pattern aggrsum(b:bat[:$tp], s:bat[:oid], wstate:ptr):$tp
address WeldAggrSum
comment "aggr.sum";

EOF
done

for func in batcalcadd:ADD batcalcsub:SUB batcalcmul:MUL batcalcdiv:DIV batcalcmod:MOD; do
    name=${func#*:}
    op=${func%:*}
    for ((i = 0; i < ${#numeric[@]}; i++)); do
		tp1=${numeric[i]}
		for ((j = 0; j < ${#numeric[@]}; j++)); do
			tp2=${numeric[j]}
			for ((k = ${#numeric[@]} - 1; k >= 0; k--)); do
				if ((k < i || k < j)); then
					continue
				fi
				tp3=${numeric[k]}
				if ((k == i || k == j)); then
					cat <<EOF
pattern $op(b1:bat[:$tp1], b2:bat[:$tp2], wstate:ptr):bat[:$tp3]
address WeldBatcalc${name}signal
comment "$op";
pattern $op(b1:bat[:$tp1], b2:bat[:$tp2], s:bat[:oid], wstate:ptr):bat[:$tp3]
address WeldBatcalc${name}signal
comment "$op with candidates list";
pattern $op(b:bat[:$tp1], v:$tp2, wstate:ptr):bat[:$tp3]
address WeldBatcalc${name}signal
comment "$op";
pattern $op(b:bat[:$tp1], v:$tp2, s:bat[:oid], wstate:ptr):bat[:$tp3]
address WeldBatcalc${name}signal
comment "$op with candidates list";
pattern $op(v:$tp1, b:bat[:$tp2], wstate:ptr):bat[:$tp3]
address WeldBatcalc${name}signal
comment "$op";
pattern $op(v:$tp1, b:bat[:$tp2], s:bat[:oid], wstate:ptr):bat[:$tp3]
address WeldBatcalc${name}signal
comment "$op with candidates list";

EOF
				fi
			done
		done
    done
done

for func in batcalclt:LT batcalcle:LE batcalceq:EQ batcalcgt:GT batcalcge:GE batcalcne:NE batcalcand:AND; do
    name=${func#*:}
    op=${func%:*}
	cat <<EOF
pattern $op(b1:bat[:any_1], b2:bat[:any_1], wstate:ptr):bat[:bit]
address WeldBatcalc${name}signal
comment "$op";
pattern $op(b1:bat[:any_1], b2:bat[:any_1], s:bat[:oid], wstate:ptr):bat[:bit]
address WeldBatcalc${name}signal
comment "$op with candidates list";
pattern $op(b:bat[:any_1], v:any_1, wstate:ptr):bat[:bit]
address WeldBatcalc${name}signal
comment "$op";
pattern $op(b:bat[:any_1], v:any_1, s:bat[:oid], wstate:ptr):bat[:bit]
address WeldBatcalc${name}signal
comment "$op with candidates list";
pattern $op(v:any_1, b:bat[:any_1], wstate:ptr):bat[:bit]
address WeldBatcalc${name}signal
comment "$op";
pattern $op(v:any_1, b:bat[:any_1], s:bat[:oid], wstate:ptr):bat[:bit]
address WeldBatcalc${name}signal
comment "$op with candidates list";

EOF
done

cat <<EOF
pattern language.pass(v:any_1, wstate:ptr):void
address WeldLanguagePass
comment "language.pass";

EOF

